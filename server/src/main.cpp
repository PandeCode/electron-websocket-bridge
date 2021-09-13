#define CROW_MAIN
#define CROW_ENABLE_DEBUG
#include "Log.hpp"
#include "crow/app.h"
#include "crow/json.h"

#include <atomic>
#include <string>
#include <string_view>

int main(int, char**) {

	const std::uint16_t                       PORT = 8080;
	crow::SimpleApp                           app;
	std::atomic<crow::websocket::connection*> globalConn = nullptr;

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
		} else {
			std::string code(crow::json::load(req.body)["command"]);
			(*globalConn)
			    .send_text(R"({"type": "code", "message": ")" + code + "\"}");
			res.add_header("Access-Control-Allow-Origin", "*");
			res.add_header("Access-Control-Allow-Headers", "Content-Type");
			return R"({"type": "info", "message", "sending command to client"})";
		}
	});

	app.route_dynamic("/command/<string>")([&](const crow::request&,
						   crow::response&   res,
						   const std::string command) {
		Log::Debug("Received REST Command: ", command);
		if(globalConn == nullptr) {
			res.code = 500;
			return R"({"message", "client not connected"})";
		} else {
			(*globalConn)
			    .send_text(
				R"({"type": "command", "message": ")" + command + "\"}");
			res.add_header("Access-Control-Allow-Origin", "*");
			res.add_header("Access-Control-Allow-Headers", "Content-Type");
			return R"({"type": "info", "message", "sending command to client"})";
		}
	});

	CROW_ROUTE(app, "/ws")
	    .websocket()
	    .onopen([&](crow::websocket::connection& conn) {
		    if(globalConn == nullptr) {
			    Log::Success("Player Client Connected: ", &conn);
			    globalConn = &conn;
		    } else {
			    Log::Info("Caught Imposter Player: ", &conn);
			    conn.close("imposter");
		    }
	    })
	    .onclose([&](crow::websocket::connection& conn, const std::string& reason) {
		    if(&conn == globalConn) {
			    Log::Warn(
				"Player Client Disconnected: ",
				&conn,
				" : ",
				reason);
			    globalConn = nullptr;
		    } else {
			    Log::Info(
				"Imposter Client Disconnected: ",
				//&conn,
				" : ",
				reason);
		    }
	    })
	    .onmessage([&](crow::websocket::connection& conn,
			   const std::string&           data,
			   bool                         is_binary) {
		    if(is_binary)
			    Log::Info("Binary Data from '", &conn, "': ", data);
		    else {
			    Log::Info("Data from '", &conn, "': ", data);

			    auto        parsedData = crow::json::load(data);
			    std::string type(parsedData["type"]);
			    std::string message(parsedData["message"]);

			    if(type == "command") {
				    if(message == "getRepeatStatus") {
					    Log::Info(
						"Player Repeat Status '",
						message,
						"'");
				    } else if(message == "getIsCurrentLiked") {
					    Log::Info(
						"Player Is Current Liked '",
						message,
						"'");
				    } else if(message == "getPlayState") {
					    Log::Info(
						"Player Play State '",
						message,
						"'");
				    } else {
					    Log::Error("Unknown command '", message, "'");
				    }
			    } else if(type == "info") {
				    Log::Info("From Player Client '", message, "'");
			    } else if(type == "error") {
				    Log::Error(
					"Error from Player Client '",
					message,
					"'");
			    } else {
				    Log::Error(
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
			    if(globalConn == nullptr) {
				    conn.send_text(
					R"({"type": "error", "message": "client not connected"})");
				    return;
			    }

			    auto        parsedData = crow::json::load(data);
			    std::string type(parsedData["type"]);
			    std::string message(parsedData["message"]);

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
					    Log::Error("Unknown Command: ", message);
					    conn.send_text(
						R"({"type": "error", "message": "unknown command ')" +
						message + "'\"}");
					    return;
				    }
			    }
		    }
	    });

	app.port(PORT).loglevel(crow::LogLevel::Critical).run();
}
