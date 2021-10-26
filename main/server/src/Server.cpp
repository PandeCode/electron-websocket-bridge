#include "server/Server.hpp"

#include "Log.hpp"

#include <array>
#include <thread>

enum class WaitMessage : std::uint8_t {
	code,
	getCurrentSong,
	getCurrentSongAlbumArt,
	getCurrentSongArtist,
	getInfo,
	getIsCurrentLiked,
	getIsPlaying,
	getRepeatStatus
};

static WaitMessage stringToWaitMessage(const std::string& str) {
	// clang-format off
	if(str == "code")                        return WaitMessage::code;
	else if(str == "getCurrentSong")         return WaitMessage::getCurrentSong;
	else if(str == "getCurrentSongAlbumArt") return WaitMessage::getCurrentSongAlbumArt;
	else if(str == "getCurrentSongArtist")   return WaitMessage::getCurrentSongArtist;
	else if(str == "getInfo")                return WaitMessage::getInfo;
	else if(str == "getIsCurrentLiked")      return WaitMessage::getIsCurrentLiked;
	else if(str == "getIsPlaying")           return WaitMessage::getIsPlaying;
	else if(str == "getRepeatStatus")        return WaitMessage::getRepeatStatus;
	// clang-format on
	else
		throw std::runtime_error("Invalid WaitMessage");
}

static std::string waitMessageToString(const WaitMessage& waitMessage) noexcept {
	switch(waitMessage) {
		case WaitMessage::code: return "code";
		case WaitMessage::getIsCurrentLiked: return "getIsCurrentLiked";
		case WaitMessage::getIsPlaying: return "getIsPlaying";
		case WaitMessage::getRepeatStatus: return "getRepeatStatus";
		case WaitMessage::getInfo: return "getInfo";
		case WaitMessage::getCurrentSongArtist: return "getCurrentSongArtist";
		case WaitMessage::getCurrentSongAlbumArt: return "getCurrentSongAlbumArt";
		case WaitMessage::getCurrentSong: return "getCurrentSong";
	}
}

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

// clang-format off
void Server::sendToAllClients(const std::string& text)   { for(const auto& client: m_clients) client->send_text(text); }
void Server::sendToAllClients(const char* text)          { for(const auto& client: m_clients) client->send_text(text); }
void Server::sendToPlayerClient(const std::string& text) { (*playerClient).send_text(text); }
void Server::sendToPlayerClient(const char* text)        { (*playerClient).send_text(text); }
// clang-format on

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
	Log::Debug("Check Give Client Call");
	for(auto& [key, value]: waitingList) {
		if(value == dataType) {
			if(std::holds_alternative<crow::response*>(key)) { // response
				Log::Debug("Check Give Client Call For RESPONSE");
				Log::Info(
				    "Rest Client [",
				    std::get<0>(key),
				    "] given '",
				    waitMessageToString(dataType),
				    "':'",
				    data,
				    "' ");

				Log::Debug("data, ", data);
				std::get<0>(key)->body = data;
				Log::Debug("Set Body");
				waitingList.erase(key);
				Log::Debug("Erased Key");
				httpLocked = false;
				Log::Debug("Http Unlocked");

			} else if(std::holds_alternative<crow::websocket::connection*>(
				      key)) { // websocket
				Log::Debug(
				    "Check Give Client Call For WEBSOCKET_CONNECTION");
				std::get<1>(key)->send_text(
				    R"({"type": ")" + waitMessageToString(dataType) +
				    R"(", "message": ")" + data + R"("})");
				waitingList.erase(key);

				Log::Info(
				    "WebSocket Client [",
				    std::get<1>(key),
				    "] sent '",
				    waitMessageToString(dataType),
				    "':'",
				    data,
				    "' ");
			} else {
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
		    Info("Accecpt: from ", req.raw_url, " :: ", req.remote_ip_address);

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
			    string             type;
			    string             message;

			    try {
				    parsedData = crow::json::load(data);
				    type       = std::string(parsedData["type"]);
				    message    = std::string(parsedData["message"]);
			    } catch(std::runtime_error err) {
				    conn.send_text(
					std::string(R"({"type": "error", "message": ")") +
					err.what() + "\"}");
				    return;
			    }

			    if(type == "code" || std::find(
						     getVaildCommands.begin(),
						     getVaildCommands.end(),
						     type) != getVaildCommands.end()) {
				    Info(
					"Got code|vaildgetcommand response '",
					type,
					"': '",
					message,
					"'");
				    checkGiveClient(stringToWaitMessage(type), message);
			    } else if(type == "info") {
				    Info("Info From Player Client '", message, "'");
			    } else if(type == "error") {
				    Error("Error from Player Client '", message, "'");
			    } else {
				    Error("Unknown type '", type, "'");
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
					std::string(R"({type: "error", "message": ")") +
					err.what() + "\"}");
				    return;
			    }

			    if(type == "code") {

				    waitingList[&conn] = WaitMessage::code;

				    sendToPlayerClient(
					R"({"type": "code", "message": ")" + message +
					"\"}");

			    } else if(type == "command") {
				    if(message != "") {

					    if(std::find(
						   getVaildCommands.begin(),
						   getVaildCommands.end(),
						   message) != getVaildCommands.end())
						    waitingList[&conn] =
							stringToWaitMessage(message);
					    else if(
						std::find(
						    validCommands.begin(),
						    validCommands.end(),
						    message) == validCommands.end()) {
						    conn.send_text(
							R"({"type": "error", "message": "unknown command ')" +
							message + R"(' "})");
						    Log::Error(
							"Unknown Command '",
							message,
							"'");
						    return;
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
			res.end();
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
			res.code = 500;
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
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(500ms);
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

constexpr const char* const Server::s_socketHelp    = R"(WebSocket Help:
Normal client websocket url
/client/ws

wscat -c "ws://localhost:8080/client/ws"

{"type": "", "message": ""}
type: info | command | code

info:
	Anything
{"type": "info", "message": "hello world this can be anything"}

code:
	Valid browser JS code
{"type": "code", "message": "document.querySelector('html').style.display = 'none'"}
{"type": "code", "message": "location.href=location.href"}

command:
    getRepeatStatus | getIsCurrentLiked | getIsPlaying | getInfo | getCurrentSong | getCurrentSongAlbumArt | getCurrentSongArtist | play | pause | playPause | next | previous | toggleLike | likeCurrent | dislikeCurrent | enableRepeat | enableRepeatOne | disableRepeat | toggleShuffle

{"type": "command", "message": "getInfo"}

{"type": "command", "message": "getRepeatStatus"}
{"type": "command", "message": "getIsCurrentLiked"}
{"type": "command", "message": "getIsPlaying"}

{"type": "command", "message": "getCurrentSong"}
{"type": "command", "message": "getCurrentSongAlbumArt"}
{"type": "command", "message": "getCurrentSongArtist"}

{"type": "command", "message": "play"}
{"type": "command", "message": "pause"}
{"type": "command", "message": "playPause"}
{"type": "command", "message": "next"}
{"type": "command", "message": "previous"}

{"type": "command", "message": "toggleLike"}
{"type": "command", "message": "likeCurrent"}
{"type": "command", "message": "dislikeCurrent"}

{"type": "command", "message": "enableRepeat"}
{"type": "command", "message": "enableRepeatOne"}
{"type": "command", "message": "disableRepeat"}

{"type": "command", "message": "toggleShuffle"}
)";

constexpr const char* const Server::s_httpHelp      = R"(Http Help:
Player client websocket url
/ws

Normal client websocket url (see websocket help)
/client/ws

HTML Sandbox to test everything (source is not compressed so you can inspect it)
/client

[POST] /code (pending repair don't use)
	curl -# -X POST -d '{"command": "location.href=location.href"}' 'http://localhost:8080/code'
	curl -#vikLd '{"command": "location.href=location.href"}' -H "Content-Type: application/json" "http://localhost:8080/code"


/command/getRepeatStatus
/command/getIsCurrentLiked
/command/getIsPlaying
/command/getInfo
/command/getCurrentSong
/command/getCurrentSongAlbumArt
/command/getCurrentSongArtist

/command/play
/command/pause
/command/playPause
/command/next
/command/previous

/command/toggleLike
/command/likeCurrent
/command/dislikeCurrent

/command/enableRepeat
/command/enableRepeatOne
/command/disableRepeat

/command/toggleShuffle

Examples
	curl "http://localhost:8080/command/getRepeatStatus"
	curl "http://localhost:8080/command/getIsCurrentLiked"
	curl "http://localhost:8080/command/getIsPlaying"
	curl "http://localhost:8080/command/getInfo"
	curl "http://localhost:8080/command/getCurrentSong"
	curl "http://localhost:8080/command/getCurrentSongAlbumArt"
	curl "http://localhost:8080/command/getCurrentSongArtist"

	curl "http://localhost:8080/command/play"
	curl "http://localhost:8080/command/pause"
	curl "http://localhost:8080/command/playPause"
	curl "http://localhost:8080/command/next"
	curl "http://localhost:8080/command/previous"

	curl "http://localhost:8080/command/toggleLike"
	curl "http://localhost:8080/command/likeCurrent"
	curl "http://localhost:8080/command/dislikeCurrent"

	curl "http://localhost:8080/command/enableRepeat"
	curl "http://localhost:8080/command/enableRepeatOne"
	curl "http://localhost:8080/command/disableRepeat"

	curl "http://localhost:8080/command/toggleShuffle"
)";

constexpr const std::array Server::getVaildCommands = {
    "getRepeatStatus",
    "getIsCurrentLiked",
    "getIsPlaying",
    "getInfo",
    "getCurrentSong",
    "getCurrentSongAlbumArt",
    "getCurrentSongArtist"};

constexpr const std::array Server::validCommands = {
    "play",
    "pause",
    "playPause",
    "next",
    "previous",
    "toggleLike",
    "likeCurrent",
    "dislikeCurrent",
    "enableRepeat",
    "enableRepeatOne",
    "disableRepeat",
    "toggleShuffle"};
