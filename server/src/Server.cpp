#include "Server.hpp"

#include "Log.hpp"


enum class WaitMessage : std::uint8_t {
	code,
	getIsCurrentLiked,
	getIsPlaying,
	getRepeatStatus
};

static WaitMessage stringToWaitMessage(const std::string& str) {
	if(str == "code")
		return WaitMessage::code;
	else if(str == "getIsCurrentLiked")
		return WaitMessage::getIsCurrentLiked;
	else if(str == "getIsPlaying")
		return WaitMessage::getIsPlaying;
	else if(str == "getRepeatStatus")
		return WaitMessage::getRepeatStatus;
	else
		throw std::runtime_error("Invalid WaitMessage");
}

static const char* waitMessageToString(const WaitMessage& waitMessage) {
	switch(waitMessage) {
		case WaitMessage::code: return "code";
		case WaitMessage::getIsCurrentLiked: return "getIsCurrentLiked";
		case WaitMessage::getIsPlaying: return "getIsPlaying";
		case WaitMessage::getRepeatStatus: return "getRepeatStatus";
	}
}

//static std::string waitMessageToString(const WaitMessage& waitMessage) {
//switch(waitMessage) {
//case WaitMessage::code: return "code";
//case WaitMessage::getIsCurrentLiked: return "getIsCurrentLiked";
//case WaitMessage::getIsPlaying: return "getIsPlaying";
//case WaitMessage::getRepeatStatus: return "getRepeatStatus";
//}
//}

static char getch() {
	char buf = 0;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
	struct termios old = {0};
#pragma clang diagnostic pop
	if(tcgetattr(0, &old) < 0) perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN]  = 1;
	old.c_cc[VTIME] = 0;
	if(tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
	if(read(0, &buf, 1) < 0) perror("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if(tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");
	return (buf);
}

Server::Server(const uint16_t& port, const crow::LogLevel& logLevel) :
    m_port(port), m_logLevel(logLevel) {
	enableAllEndpoints();
}

Server::~Server() {
	if(playerClient != nullptr) (*playerClient).close();
	for(const auto& client: m_clients)
		client->close();
}

void Server::startServer() {
	std::thread waitForEnterKeyThread(&Server::waitForEnterKey, this);
	m_app.port(m_port).loglevel(m_logLevel).multithreaded().run();
	waitForEnterKeyThread.join();
	Log::Debug("Server Shutdown");
}

void Server::sendToAllClients(const char* text) {
	for(const auto& client: m_clients)
		client->send_text(text);
}

void Server::sendToPlayerClient(const char* text) {
	(*playerClient).send_text(text);
}

void Server::killServer() {
	Log::Debug("Requested Server Shutdown");

	if(playerClient != nullptr) (*playerClient).close();
	for(const auto& client: m_clients)
		client->close();

	m_app.stop();
}

void Server::waitForEnterKey() {
	while(1) {
		switch(getch()) {
			case 12:
				{
					std::system("clear");
					break;
				}
			case 'd':
				{
					Log::Warn("Disconnecting Clients");

					if(playerClient != nullptr)
						(*playerClient).close();
					for(const auto& client: m_clients)
						client->close();

					break;
				}
			case 03:
			case 'q':
				{
					killServer();
					return;
				}
			case 'w':
				{
					for(auto& [key, value]: waitingList) {
						if(std::holds_alternative<
						       crow::response*>(key))
							Log::Info(
							    "Rest (",
							    std::get<0>(key),
							    ") waiting for  ",
							    waitMessageToString(value));
						else if(std::holds_alternative<
							    crow::websocket::connection*>(
							    key))
							Log::Info(
							    "WebSocket Client (",
							    std::get<1>(key),
							    ") waiting for  ",
							    waitMessageToString(value));
					}
					break;
				}
			case 'l':
			case 'i':
				{
					if(playerClient == nullptr)
						Log::Warn("Player Client Not Connected");
					else
						Log::Info(
						    "Player Client: ",
						    &(*playerClient));

					Log::Info("Clients [", m_clients.size(), "]");
					for(std::uint16_t i = 0; i != m_clients.size();
					    i++)
						Log::Info("[", i, "] : ", m_clients[i]);

					break;
				}
			case 'p':
				{
					Log::Info("Ping All Clients");
					sendToAllClients(
					    R"({"type": "info", "message": "ping"})");
					break;
				}
			case '?':
			case 'h':
				{
					Log::Info(s_httpHelp, s_socketHelp);
					break;
				}
			default: break;
		}
	}
}

void Server::enableAllEndpoints() {
	enableClientWebsocket();
	enablePlayerClientWebsocket();
	enableHelpEndpoints();
	enableHttpClient();
	enableHtmlClient();
}

void Server::checkGiveClient(const WaitMessage dataType, const std::string& data) {
	Log::Debug("Key ");
	for(auto& [key, value]: waitingList) {
		if(value == dataType) {
			if(std::holds_alternative<crow::response*>(key)) //response
			{

				Log::Info("Yes");
				Log::Info(
				    "Rest Client [",
				    std::get<1>(key),
				    "] given '",
				    waitMessageToString(dataType),
				    "':'",
				    data,
				    "' ");
				std::get<0>(key)->body = data;
				Log::Debug("Set Body");
				waitingList.erase(key);
				Log::Debug("Erased Key");
				httpLocked = false;
				Log::Debug("Http Unlocked");

			} else if(std::holds_alternative<crow::websocket::connection*>(
				      key)) //websocket
			{
				std::get<1>(key)->send_text(
				    std::string(R"({"type": ")") +
				    waitMessageToString(dataType) + R"(", "message": ")" +
				    data + R"("})");
				waitingList.erase(key);

				Log::Info(
				    "WebSocket Client [",
				    std::get<1>(key),
				    "] sent '",
				    waitMessageToString(dataType),
				    "':'",
				    data,
				    "' ");
			}else{
				Log::Error("Neither");
			}
			break;
		}
	}
}

void Server::enablePlayerClientWebsocket() {
	using namespace std;
	using namespace Log;

	CROW_ROUTE(m_app, "/ws")
	    .websocket()
	    .onaccept([&](const crow::request& req) {
		    Info(
			"Accecpt: ",
			" :: ",
			req.body,
			" :: ",
			req.url,
			" :: ",
			req.raw_url,
			" :: ",
			req.remote_ip_address);

		    if(playerClient != nullptr) {
			    Info("Imposter client blocked, already connected.");
			    return false;
		    }

		    return true;
	    })
	    .onerror([&](crow::websocket::connection& conn) {
		    Error("Error with '", &conn, "'");
	    })
	    .onopen([&](crow::websocket::connection& conn) {
		    if(playerClient == nullptr) {
			    Success("Player Client Connected: ", &conn);
			    playerClient = &conn;
		    } else {
			    Info("Imposter What: ", &conn);
		    }
	    })
	    .onclose([&](crow::websocket::connection& conn, const string& reason) {
		    if(&conn == playerClient) {
			    Warn("Player Client Disconnected: ", &conn, " : ", reason);
			    playerClient = nullptr;
		    } else {
			    Info("Imposter Client Disconnected: ", &conn, " : ", reason);
		    }
	    })
	    .onmessage([&](crow::websocket::connection& conn,
			   const string&                data,
			   bool                         is_binary) {
		    if(is_binary)
			    Info("Binary Data from '", &conn, "': ", data);
		    else {

			    crow::json::rvalue parsedData;
			    try {
				    parsedData = crow::json::load(data);
			    } catch(std::runtime_error err) {
				    conn.send_text(
					std::string(R"({type: error, "message": ")") +
					err.what() + "\"}");
			    }

			    string type(parsedData["type"]);
			    string message(parsedData["message"]);

			    if(type == "code") {
				    Info("Got code response '", message, "'");
				    checkGiveClient(WaitMessage::code, message);
			    } else if(type == "getRepeatStatus") {
				    Info("Repeat Status '", message, "'");
				    checkGiveClient(
					WaitMessage::getRepeatStatus,
					message);
			    } else if(type == "getIsCurrentLiked") {
				    Info("Is Current Liked '", message, "'");
				    checkGiveClient(
					WaitMessage::getIsCurrentLiked,
					message);
			    } else if(type == "getIsPlaying") {
				    Info("Is Playing '", message, "'");
				    checkGiveClient(WaitMessage::getIsPlaying, message);
			    } else if(type == "info") {
				    Info("Info From Player Client '", message, "'");
			    } else if(type == "error") {
				    Error("Error from Player Client '", message, "'");
			    } else {
				    Error(
					"Unknown type '",
					type,
					"' with '",
					message,
					"'");
			    }
		    }
	    });
}

void Server::enableHelpEndpoints() {
	CROW_ROUTE(m_app, "/")
	([&]() { return s_httpHelp; });
	CROW_ROUTE(m_app, "/command")
	([&]() { return s_httpHelp; });
	CROW_ROUTE(m_app, "/help")
	([&]() { return s_httpHelp; });
	CROW_ROUTE(m_app, "/code")
	([&]() { return s_httpHelp; });
}

void Server::enableClientWebsocket() {
	CROW_ROUTE(m_app, "/client/ws")
	    .websocket()
	    .onopen([&](crow::websocket::connection& conn) {
		    Log::Success("Client Connected: ", &conn);
		    m_clients.push_back(&conn);
	    })
	    .onclose([&](crow::websocket::connection& conn, const std::string& reason) {
		    Log::Info("Client Disconnected: ", &conn, " : ", reason);
		    m_clients.erase(std::find(m_clients.begin(), m_clients.end(), &conn));
	    })
	    .onmessage([&](crow::websocket::connection& conn,
			   const std::string&           data,
			   bool                         is_binary) {
		    if(is_binary)
			    Log::Info("Binary Data from '", &conn, "': ", data);
		    else {
			    Log::Info("Data from '", &conn, "': ", data);
			    if(data == "help" || data == "?" || data == "h") {
				    conn.send_text(s_socketHelp);
				    return;
			    }
			    if(playerClient == nullptr) {
				    conn.send_text(
					R"({"type": "error", "message": "client not connected"})");
				    return;
			    }
			    crow::json::rvalue parsedData;
			    std::string        type;
			    std::string        message;
			    try {
				    parsedData = crow::json::load(data);
				    type       = std::string(parsedData["type"]);
				    message    = std::string(parsedData["message"]);
			    } catch(std::runtime_error err) {
				    conn.send_text(
					std::string(R"({type: error, "message": ")") +
					err.what() + "\"}");
			    }

			    if(type == "code") {

				    waitingList[&conn] = WaitMessage::code;

				    (*playerClient)
					.send_text(
					    R"({"type": "code", "message": ")" + message +
					    "\"}");

			    } else if(type == "command") {
				    if(message != "") {

					    if(message == "getRepeatStatus") {

						    waitingList[&conn] =
							WaitMessage::getRepeatStatus;

					    } else if(message == "getIsCurrentLiked") {

						    waitingList[&conn] =
							WaitMessage::getIsCurrentLiked;

					    } else if(message == "getIsPlaying") {

						    waitingList[&conn] =
							WaitMessage::getIsPlaying;
					    }

					    (*playerClient).send_text(data);

				    } else {
					    Log::Error("Blank Command: ", message);
					    conn.send_text(
						R"({"type": "error", "message": "blank command ')" +
						message + "'\"}");
					    return;
				    }
			    } else if(type == "info") {
				    conn.send_text(
					R"({"type": "info", "message": ")" +
					std::string(s_socketHelp) + "\"}");
			    } else {
				    Log::Error("Unknown Type: '", type, "'");
				    conn.send_text(
					R"({"type": "error", "message": "unknown command ')" +
					message + "'\"}");
				    return;
			    }
		    }
	    });
}

void Server::enableHttpClient() {
	m_app.route_dynamic("/code").methods(
	    crow::HTTPMethod::POST)([&](const crow::request& req, crow::response& res) {
		if(playerClient == nullptr) {
			res.code = 500;
			return R"({"type": "error", "message": "client not connected"})";
		}

		res.add_header("Access-Control-Allow-Origin", "*");
		res.add_header("Content-Type", "application/json");

		crow::json::rvalue parsedData;
		try {
			parsedData = crow::json::load(req.body);
		} catch(std::runtime_error err) {
			res.body = std::string(R"({"type": "error", "message": ")") +
				   err.what() + "\"}";
			res.code = 400;
			res.end();
			return res.body.c_str();
		}

		std::string code(parsedData["command"]);

		waitingList[&res] = WaitMessage::code;

		(*playerClient)
		    .send_text(R"({"type": "code", "message": ")" + code + "\"}");

		// wait for signal from other thread
		Log::Info(
		    "Rest Sent callback command to player '",
		    code,
		    "' for '",
		    &res,
		    "'");
		httpLocked = true;
		Log::Debug("Http Locked");

		while(httpLocked) {
			Log::Info("Locked Command");
			sleep(1);
		}
		Log::Info(
		    "Rest Received callback command to player '",
		    code,
		    "' for '",
		    &res,
		    "' data '",
		    res.body,
		    "'");

		res.end();
		return res.body.c_str();
	});

	m_app.route_dynamic("/command/<string>")([&](const crow::request&,
						     crow::response&   res,
						     const std::string command) {
		Log::Debug("Received REST Command: ", command);

		res.add_header("Access-Control-Allow-Origin", "*");
		res.add_header("Content-Type", "application/json");

		if(playerClient == nullptr) {
			res.code = 500;
			return R"({"type": "error", "message": "client not connected"})";
		}

		if(command == "getRepeatStatus" || command == "getIsCurrentLiked" ||
		   command == "getIsPlaying") {
			waitingList[&res] = stringToWaitMessage(command);
			(*playerClient)
			    .send_text(
				R"({"type": "command", "message": ")" + command + "\"}");

			// wait for signal from other thread
			Log::Info(
			    "Rest Sent callback command to player '",
			    command,
			    "' for '",
			    &res,
			    "'");
			httpLocked = true;
			while(httpLocked) {
				Log::Info("Locked Command");
				sleep(1);
			}
			Log::Info(
			    "Rest Received callback command to player '",
			    command,
			    "' for '",
			    &res,
			    "' data '",
			    res.body,
			    "'");

			res.end();
			return res.body.c_str();
		} else {
			(*playerClient)
			    .send_text(
				R"({"type": "command", "message": ")" + command + "\"}");
			res.end();
			return R"({"type": "info", "message": "sending command to client"})";
		}
	});
}

void Server::enableHtmlClient() {
	CROW_ROUTE(m_app, "/client/tailwind.css")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info("/home/shawn/dev/cpp/CLIProjeccts/"
					 "SpotifyHack/client/tailwind.css");
		res.end();
	});

	CROW_ROUTE(m_app, "/client/rest.js")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info("/home/shawn/dev/cpp/CLIProjeccts/"
					 "SpotifyHack/client/rest.js");
		res.end();
	});

	CROW_ROUTE(m_app, "/client/socket.js")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info("/home/shawn/dev/cpp/CLIProjeccts/"
					 "SpotifyHack/client/socket.js");
		res.end();
	});

	CROW_ROUTE(m_app, "/client/rtc.js")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info(
		    "/home/shawn/dev/cpp/CLIProjeccts/SpotifyHack/client/rtc.js");
		res.end();
	});

	CROW_ROUTE(m_app, "/client")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info("/home/shawn/dev/cpp/CLIProjeccts/"
					 "SpotifyHack/client/client.html");
		res.end();
	});
}

constexpr const char* const Server::s_socketHelp = R"(HttpHelp
{"type": "", "message": ""}
type: info | command | code
Examples
{"type": "command", "message": "playPause"}
{"type": "command", "message": "play"}
{"type": "command", "message": "pause"}
{"type": "command", "message": "next"}
)";

constexpr const char* const Server::s_httpHelp   = R"(Socket Help:
/ws
/client
/client/ws
/command/disableRepeatOne
/command/dislikeCurrent
"command/enableRepeat
/command/enableRepeatOne
/command/likeCurrent
/command/next
/command/pause
/command/play
/command/playPause
/command/previous
/command/toggleLikeCurrent
/command/toggleShuffle

/command/getInfo

[POST] /code
Examples
	curl -# -X POST -d '{"command": "location.href=location.href"}' 'http://localhost:8080/code'
	curl -#vikLd '{"command": "location.href=location.href"}' -H "Content-Type: application/json" "http://localhost:8080/code"
)";
