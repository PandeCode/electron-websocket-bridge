#define CROW_MAIN
#define CROW_ENABLE_DEBUG
#include "Log.hpp"
#include "crow/app.h"
#include "crow/json.h"

#include <atomic>
#include <cstdlib>
#include <string>
#include <string_view>

const char* sockethelp = R"(

)";

int main(int argc, char** argv) {
	using namespace std;
	using namespace Log;

	std::uint16_t PORT = 8080;
	if(argc > 1) PORT = std::atoi(argv[1]);
	crow::SimpleApp                      app;
	atomic<crow::websocket::connection*> globalConn = nullptr;

	CROW_ROUTE(app, "/")
	([&]() {
		return "Help:\n/command/disableRepeatOne\n/command/dislikeCurrent\n/"
		       "command/enableRepeat\n/command/enableRepeatOne\n/command/"
		       "isCurrentLiked\n/command/likeCurrent\n/command/next\n/command/"
		       "pause\n/command/play\n/command/playPause\n/command/playState\n/"
		       "command/previous\n/command/repeatStatus\n/command/"
		       "toggleLikeCurrent\n/command/toggleShuffle\n";
	});

	app.route_dynamic("/code").methods(
	    crow::HTTPMethod::POST)([&](const crow::request& req, crow::response& res) {
		if(globalConn == nullptr) {
			res.code = 500;
			return R"({"message", "client not connected"})";
		}
		string code(crow::json::load(req.body)["command"]);
		(*globalConn)
		    .send_text(R"({"type": "code", "message": ")" + code + "\"}");
		res.add_header("Access-Control-Allow-Origin", "*");
		res.add_header("Content-Type", "application/json");
		res.body = R"({"type": "info", "message", "sending command to client"})";

		res.end();
		return res.body.c_str();
	});

	app.route_dynamic("/command/<string>")([&](const crow::request&,
						   crow::response& res,
						   const string    command) {
		Debug("Received REST Command: ", command);
		if(globalConn == nullptr) {
			res.code = 500;
			return R"({"message", "client not connected"})";
		}
		(*globalConn)
		    .send_text(R"({"type": "command", "message": ")" + command + "\"}");
		res.add_header("Access-Control-Allow-Origin", "*");

		res.add_header("Content-Type", "application/json");
		res.body = R"({"type": "info", "message", "sending command to client"})";
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
			    auto   parsedData = crow::json::load(data);
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
				    Info("Got code response '", message,"'");
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

	CROW_ROUTE(app, "/client/main.js")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info("/home/shawn/dev/cpp/CLIProjeccts/"
					 "SpotifyHack/client/main.js");
		res.end();
	});

	CROW_ROUTE(app, "/client/socketMain.js")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info("/home/shawn/dev/cpp/CLIProjeccts/"
					 "SpotifyHack/client/socketMain.js");
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
			    if(globalConn == nullptr) {
				    conn.send_text(
					R"({"type": "error", "message": "client not connected"})");
				    return;
			    }
			    auto   parsedData = crow::json::load(data);
			    string type(parsedData["type"]);
			    string message(parsedData["message"]);
			    if(type == "code") {
				    (*globalConn)
					.send_text(
					    R"({"type": "code", "message": ")" + message +
					    "\"}");
			    } else if(type == "command") {
				    if(message == "disableRepeatOne") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "disableRepeatOne"})");
				    } else if(message == "dislikeCurrent") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "dislikeCurrent"})");
				    } else if(message == "enableRepeat") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "enableRepeat"})");
				    } else if(message == "enableRepeatOne") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "enableRepeatOne"})");
				    } else if(message == "isCurrentLiked") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "isCurrentLiked"})");
				    } else if(message == "likeCurrent") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message", "likeCurrent"})");
				    } else if(message == "next") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "next"})");
				    } else if(message == "pause") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "pause"})");
				    } else if(message == "play") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "play"})");
				    } else if(message == "playPause") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "playPause"})");
				    } else if(message == "playState") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "playState"})");
				    } else if(message == "previous") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "previous"})");
				    } else if(message == "repeatStatus") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "repeatStatus"})");
				    } else if(message == "toggleLikeCurrent") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "toggleLikeCurrent"})");
				    } else if(message == "toggleShuffle") {
					    (*globalConn)
						.send_text(
						    R"({"type": "command", "message": "toggleShuffle"})");
				    } else {
					    Error("Unknown Command: ", message);
					    conn.send_text(
						R"({"type": "error", "message": "unknown command ')" +
						message + "'\"}");
					    return;
				    }
			    }
		    }
	    });

	app.port(PORT).loglevel(crow::LogLevel::Info).run();
}
