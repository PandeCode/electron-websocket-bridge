#define CROW_MAIN
#include "crow/app.h"

#include <atomic>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

//

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void my_handler(int s) {
	std::cout << "Caught signal " << s << std::endl;
}

int main(int, char**) {

	signal(SIGINT, my_handler);

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

	CROW_ROUTE(app, "/command/<string>")
	([&](const std::string& command) {
		std::cout << command << std::endl;
		if(globalConn == nullptr) {
			return std::string("Not yet connected to client");
		} else {
			(*globalConn).send_text(command);

			//res.add_header("Access-Control-Allow-Origin", "*");
			//res.add_header("Access-Control-Allow-Headers", "Content-Type");

			return "Sending: '" + std::string(command) + "'\n";
		}
	});

	CROW_ROUTE(app, "/ws")
	    .websocket()
	    .onopen([&](crow::websocket::connection& conn) {
		    if(globalConn == nullptr) {
			    std::cout << "Client Connected: " << &conn << "\n";
			    globalConn = &conn;
		    } else {
			    std::cout << "Caught Imposter: " << &conn << "\n";
			    conn.close("imposter");
		    }
	    })
	    .onclose([&](crow::websocket::connection& conn, const std::string& reason) {
		    if(&conn == globalConn) {
			    std::cout << "Client Disconnected: " << &conn << " : "
				      << reason << std::endl;
			    globalConn = nullptr;
		    } else {
			    std::cout << "Imposter Client Disconnected: " << &conn
				      << " : " << reason << std::endl;
		    }
	    })
	    .onmessage([&](crow::websocket::connection& conn,
			   const std::string&           data,
			   bool                         is_binary) {
		    if(is_binary)
			    std::cout << "Binary Data from '" << &conn << "': " << data
				      << std::endl;
		    else {
			    std::cout << "Data from '" << &conn << "': " << data
				      << std::endl;

			    if(data.substr(0, 10) == "playState:") {
				    std::cout
					<< "playState: " << data.substr(10, data.size())
					<< std::endl;
			    } else if(data.substr(0, 6) == "Error:") {
				    std::cout << "Error: " << data.substr(6, data.size())
					      << std::endl;
			    } else if(data.substr(0, 15) == "isCurrentLiked:") {
				    std::cout << "isCurrentLiked: "
					      << data.substr(15, data.size())
					      << std::endl;
			    } else if(data.substr(0, 13) == "repeatStatus:") {
				    std::cout << "repeatStatus: "
					      << data.substr(13, data.size())
					      << std::endl;
			    }
		    }
	    });

	CROW_ROUTE(app, "/client/main.js")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info(
		    "/home/shawn/dev/cpp/CLIProjeccts/SpotifyHack/client/main.js");
		res.end();
	});

	CROW_ROUTE(app, "/client/socketMain.js")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info(
		    "/home/shawn/dev/cpp/CLIProjeccts/SpotifyHack/client/socketMain.js");
		res.end();
	});

	CROW_ROUTE(app, "/client")
	([](const crow::request&, crow::response& res) {
		res.set_static_file_info(
		    "/home/shawn/dev/cpp/CLIProjeccts/SpotifyHack/client/client.html");
		res.end();
	});

	CROW_ROUTE(app, "/client/ws")
	    .websocket()
	    .onopen([&](crow::websocket::connection& conn) {
		    std::cout << "Client Connected: " << &conn << "\n";
	    })
	    .onclose([&](crow::websocket::connection& conn, const std::string& reason) {
		    std::cout << "Client Disconnected: " << &conn << " : " << reason
			      << std::endl;
	    })
	    .onmessage([&](crow::websocket::connection& conn,
			   const std::string&           data,
			   bool                         is_binary) {
		    if(is_binary)
			    std::cout << "Binary Data from '" << &conn << "': " << data
				      << std::endl;
		    else {
			    std::cout << "Data from ;" << &conn << "': " << data
				      << std::endl;
			    if(globalConn == nullptr) {
				    conn.send_text("Error: player client not connnected");
				    return;
			    }
			    if(data == "disableRepeatOne")
				    (*globalConn).send_text("disableRepeatOne");
			    else if(data == "dislikeCurrent")
				    (*globalConn).send_text("dislikeCurrent");
			    else if(data == "enableRepeat")
				    (*globalConn).send_text("enableRepeat");
			    else if(data == "enableRepeatOne")
				    (*globalConn).send_text("enableRepeatOne");
			    else if(data == "isCurrentLiked")
				    (*globalConn).send_text("isCurrentLiked");
			    else if(data == "likeCurrent")
				    (*globalConn).send_text("likeCurrent");
			    else if(data == "next")
				    (*globalConn).send_text("next");
			    else if(data == "pause")
				    (*globalConn).send_text("pause");
			    else if(data == "play")
				    (*globalConn).send_text("play");
			    else if(data == "playPause")
				    (*globalConn).send_text("playPause");
			    else if(data == "playState")
				    (*globalConn).send_text("playState");
			    else if(data == "previous")
				    (*globalConn).send_text("previous");
			    else if(data == "repeatStatus")
				    (*globalConn).send_text("repeatStatus");
			    else if(data == "toggleLikeCurrent")
				    (*globalConn).send_text("toggleLikeCurrent");
			    else if(data == "toggleShuffle")
				    (*globalConn).send_text("toggleShuffle");
			    else {
				    std::cout << "Unknown Command: " << data << std::endl;
			    }
		    }
	    });

	app.port(PORT).loglevel(crow::LogLevel::Critical).run();
}
