#define CROW_MAIN
#define CROW_ENABLE_DEBUG
#include "Log.hpp"
#include "crow/app.h"
#include "crow/json.h"

#include <atomic>
#include <cstdlib>
#include <string>
#include <string_view>
#include <unordered_map>

constexpr const char* socketHelp = R"(
{"type": "", "message": ""}

type: info | command | code

Examples
{"type": "command", "message": "playPause"}
{"type": "command", "message": "play"}
{"type": "command", "message": "pause"}
{"type": "command", "message": "next"}
)";

constexpr const char* httpHelp   = R"(Help:

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

int main(int argc, char** argv) {
	using namespace std;
	using namespace Log;

	uint16_t PORT = 8080;
	if(argc > 1) PORT = atoi(argv[1]);
	crow::SimpleApp                      app;
	atomic<crow::websocket::connection*> globalConn = nullptr;

	CROW_ROUTE(app, "/")
	([&]() { return httpHelp; });
	CROW_ROUTE(app, "/command")
	([&]() { return httpHelp; });
	CROW_ROUTE(app, "/help")
	([&]() { return httpHelp; });
	CROW_ROUTE(app, "/code")
	([&]() { return httpHelp; });

	app.route_dynamic("/code").methods(
	    crow::HTTPMethod::POST)([&](const crow::request& req, crow::response& res) {
		if(globalConn == nullptr) {
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

		string code(parsedData["command"]);

		(*globalConn)
		    .send_text(R"({"type": "code", "message": ")" + code + "\"}");
		res.body = R"({"type": "info", "message": "sending command to client"})";
		res.end();
		return res.body.c_str();
	});

	app.route_dynamic("/command/<string>")([&](const crow::request&,
						   crow::response& res,
						   const string    command) {
		Debug("Received REST Command: ", command);
		if(globalConn == nullptr) {
			res.code = 500;
			return R"({"type": "error", "message": "client not connected"})";
		}
		(*globalConn)
		    .send_text(R"({"type": "command", "message": ")" + command + "\"}");
		res.add_header("Access-Control-Allow-Origin", "*");

		res.add_header("Content-Type", "application/json");
		res.body = R"({"type": "info", "message": "sending command to client"})";
		res.end();
		return res.body.c_str();
	});

	CROW_ROUTE(app, "/ws")
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

		    if(globalConn != nullptr) {
			    Info("Imposter client blocked, already connected.");
			    return false;
		    }

		    return true;
	    })
	    .onerror([&](crow::websocket::connection& conn) {
		    Error("Error with '", &conn, "'");
	    })
	    .onopen([&](crow::websocket::connection& conn) {
		    if(globalConn == nullptr) {
			    Success("Player Client Connected: ", &conn);
			    globalConn = &conn;
		    } else {
			    Info("Imposter What: ", &conn);
		    }
	    })
	    .onclose([&](crow::websocket::connection& conn, const string& reason) {
		    if(&conn == globalConn) {
			    Warn("Player Client Disconnected: ", &conn, " : ", reason);
			    globalConn = nullptr;
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

	CROW_ROUTE(app, "/client/tailwind.css")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info("/home/shawn/dev/cpp/CLIProjeccts/"
					 "SpotifyHack/client/tailwind.css");
		res.end();
	});

	CROW_ROUTE(app, "/client/http.js")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info("/home/shawn/dev/cpp/CLIProjeccts/"
					 "SpotifyHack/client/http.js");
		res.end();
	});

	CROW_ROUTE(app, "/client/socket.js")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info("/home/shawn/dev/cpp/CLIProjeccts/"
					 "SpotifyHack/client/socket.js");
		res.end();
	});

	CROW_ROUTE(app, "/client/rtc.js")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info(
		    "/home/shawn/dev/cpp/CLIProjeccts/SpotifyHack/client/rtc.js");
		res.end();
	});

	CROW_ROUTE(app, "/client")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info("/home/shawn/dev/cpp/CLIProjeccts/"
					 "SpotifyHack/client/client.html");
		res.end();
	});

	CROW_ROUTE(app, "/client/ws")
	    .websocket()
	    .onopen([&](crow::websocket::connection& conn) {
		    Success("Client Connected: ", &conn);
	    })
	    .onclose([&](crow::websocket::connection& conn, const string& reason) {
		    Info("Client Disconnected: ", &conn, " : ", reason);
	    })
	    .onmessage([&](crow::websocket::connection& conn,
			   const string&                data,
			   bool                         is_binary) {
		    if(is_binary)
			    Info("Binary Data from '", &conn, "': ", data);
		    else {
			    Info("Data from '", &conn, "': ", data);

			    if(data == "help" || data == "?" || data == "h") {
				    conn.send_text(socketHelp);
				    return;
			    }

			    if(globalConn == nullptr) {
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

			    string type(parsedData["type"]);
			    string message(parsedData["message"]);

			    if(type == "code") {
				    (*globalConn)
					.send_text(
					    R"({"type": "code", "message": ")" + message +
					    "\"}");
			    } else if(type == "command") {
				    if(message != "")
					    (*globalConn).send_text(data);
				    else {
					    Error("Blank Command: ", message);
					    conn.send_text(
						R"({"type": "error", "message": "unknown command ')" +
						message + "'\"}");
					    return;
				    }
			    } else if(type == "info") {
				    conn.send_text(
					R"({"type": "info", "message": ")" +
					std::string(socketHelp) + "\"}");
			    } else {
				    Error("Unknown Type: '", type, "'");
				    conn.send_text(
					R"({"type": "error", "message": "unknown command ')" +
					message + "'\"}");
				    return;
			    }
		    }
	    });

	app.port(PORT).loglevel(crow::LogLevel::Info).run();
}
