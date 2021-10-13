#pragma once

#include <iostream>
#include <thread>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> Client;

// pull out the type of messages sent by our config
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

// This message handler will be invoked once for each incoming message. It
// prints the message and then sends a copy of the message back to the server.
void on_message(Client* c, websocketpp::connection_hdl hdl, message_ptr msg);

class WebSocket {
	Client                      c;
	websocketpp::connection_hdl hdl;
	std::string                 m_uri;
	std::thread                 connThread;

      public:
	WebSocket(const std::string& uri = "ws://localhost:8080/client/ws");
	~WebSocket();

	void sendMessage(const std::string& type, const std::string& message);
	void activate();

	void toggleShuffle();
	void playPause();
	void enableRepeat();
	void toggleLike();
	void likeCurrent();
	void disableRepeat();
	void previous();
	void enableRepeatOne();
	void play();
	void next();
	void pause();
	void dislikeCurrent();
};
