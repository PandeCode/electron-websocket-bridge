#include "Server.hpp"

#include "Log.hpp"

static char getch() {
	char           buf = 0;
	struct termios old = {0};
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

void Server::startServer() {
	std::thread waitForEnterKeyThread(&Server::waitForEnterKey, this);

	m_app.port(m_port).loglevel(m_logLevel).run();

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

void Server::waitForEnterKey() {
	while(1) {
		char ch = getch();
		if(ch == 12)
			std::system("clear");
		else if(ch == 'l' || ch =='i') {
			// TODO: Implement
			Log::Info("List Clients");
		}
		else if(ch == 'p') {
			Log::Info("Ping All Clients");
			sendToAllClients(R"({"type": "info", "message": "ping"})");
		} else if(ch == '?' || ch == 'h')
			Log::Info(s_httpHelp, s_socketHelp);
	}
}

void Server::enableAllEndpoints() {
	enableClientWebsocket();
	enablePlayerClientWebsocket();
	enableHelpEndpoints();
	enableHttpClient();
	enableHtmlClient();
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

			    if(type == "getRepeatStatus") {
				    Info("Repeat Status '", message, "'");
			    } else if(type == "getIsCurrentLiked") {
				    Info("Is Current Liked '", message, "'");
			    } else if(type == "getIsPlaying") {
				    Info("Is Playing '", message, "'");
			    } else if(type == "info") {
				    Info("Info From Player Client '", message, "'");
			    } else if(type == "error") {
				    Error("Error from Player Client '", message, "'");
			    } else if(type == "code") {
				    Info("Got code response '", message, "'");
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
	    })
	    .onclose([&](crow::websocket::connection& conn, const std::string& reason) {
		    Log::Info("Client Disconnected: ", &conn, " : ", reason);
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
			    try {
				    parsedData = crow::json::load(data);
			    } catch(std::runtime_error err) {
				    conn.send_text(
					std::string(R"({type: error, "message": ")") +
					err.what() + "\"}");
			    }
			    std::string type(parsedData["type"]);
			    std::string message(parsedData["message"]);
			    if(type == "code") {
				    (*playerClient)
					.send_text(
					    R"({"type": "code", "message": ")" + message +
					    "\"}");
			    } else if(type == "command") {
				    if(message != "")
					    (*playerClient).send_text(data);
				    else {
					    Log::Error("Blank Command: ", message);
					    conn.send_text(
						R"({"type": "error", "message": "unknown command ')" +
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

		(*playerClient)
		    .send_text(R"({"type": "code", "message": ")" + code + "\"}");
		res.body = R"({"type": "info", "message": "sending command to client"})";
		res.end();
		return res.body.c_str();
	});

	m_app.route_dynamic("/command/<string>")([&](const crow::request&,
						     crow::response&   res,
						     const std::string command) {
		Log::Debug("Received REST Command: ", command);
		if(playerClient == nullptr) {
			res.code = 500;
			return R"({"type": "error", "message": "client not connected"})";
		}
		(*playerClient)
		    .send_text(R"({"type": "command", "message": ")" + command + "\"}");
		res.add_header("Access-Control-Allow-Origin", "*");

		res.add_header("Content-Type", "application/json");
		res.body = R"({"type": "info", "message": "sending command to client"})";
		res.end();
		return res.body.c_str();
	});
}

void Server::enableHtmlClient() {
	CROW_ROUTE(m_app, "/client/tailwind.css")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info("/home/shawn/dev/cpp/CLIProjeccts/"
					 "SpotifyHack/client/tailwind.css");
		res.end();
	});

	CROW_ROUTE(m_app, "/client/http.js")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info("/home/shawn/dev/cpp/CLIProjeccts/"
					 "SpotifyHack/client/http.js");
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
/command/isCurrentLiked
/command/likeCurrent
/command/next
/command/pause
/command/play
/command/playPause
/command/getIsPlaying
"command/previous
/command/repeatStatus
/command/toggleLikeCurrent
/command/toggleShuffle
[POST] /code
Examples
	curl -# -X POST -d '{"command": "location.href=location.href"}' 'http://localhost:8080/code'
	curl -#vikLd '{"command": "location.href=location.href"}' -H "Content-Type: application/json" "http://localhost:8080/code"
)";
