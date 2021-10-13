#include "WebSocket.hpp"

#include "Log.hpp"

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

void on_message(Client*, websocketpp::connection_hdl hdl, message_ptr msg) {
	Log::Info(
	    "hdl: ",
	    hdl.lock().get(),
	    " got  message from server: ",
	    msg->get_payload());

	websocketpp::lib::error_code ec;
	//c->send(hdl, msg->get_payload(), msg->get_opcode(), ec);
	if(ec) Log::Error("Echo failed because: ", ec.message());
}

WebSocket::WebSocket(const std::string& uri) : m_uri(uri) { }

void WebSocket::activate(){
	try {
		// Set logging to be pretty verbose (everything except message payloads)
		c.set_access_channels(websocketpp::log::alevel::all);
		c.clear_access_channels(websocketpp::log::alevel::frame_payload);

		// Initialize ASIO
		c.init_asio();

		// Register our message handler
		c.set_message_handler(bind(&on_message, &c, ::_1, ::_2));
		// TODO: Make More Handlers

		websocketpp::lib::error_code ec;
		Client::connection_ptr       con = c.get_connection(m_uri, ec);
		if(ec) {
			throw std::runtime_error(
			    "could not create connection because: " + ec.message());
		}

		// Note that connect here only requests a connection. No network messages are
		// exchanged until the event loop starts running in the next line.
		c.connect(con);
		hdl = con->get_handle();

		// Start the ASIO io_service run loop
		// this will cause a single connection to be made to the server. c.run()
		// will exit when this connection is closed.
		Log::Debug("Blocking");
		connThread = std::thread([this]() { this->c.run(); });
		Log::Debug("Not Blocking");
	} catch(websocketpp::exception const & e) { Log::Error(e.what()); }

}

WebSocket::~WebSocket() {
	connThread.join();
}

void WebSocket::sendMessage(const std::string& type, const std::string& message) {
	websocketpp::lib::error_code ec;

	c.send(
	    hdl,
	    R"({"type": ")" + type + R"(", "message": ")" + message + R"("})",
	    websocketpp::frame::opcode::text,
	    ec);

	if(ec) Log::Error("Error sending message to Server");
}

// clang-format off
void WebSocket::toggleShuffle()   { sendMessage("command", "toggleShuffle"   ); }
void WebSocket::playPause()       { sendMessage("command", "playPause"       ); }
void WebSocket::enableRepeat()    { sendMessage("command", "enableRepeat"    ); }
void WebSocket::toggleLike()      { sendMessage("command", "toggleLike"      ); }
void WebSocket::likeCurrent()     { sendMessage("command", "likeCurrent"     ); }
void WebSocket::disableRepeat()   { sendMessage("command", "disableRepeat"   ); }
void WebSocket::previous()        { sendMessage("command", "previous"        ); }
void WebSocket::enableRepeatOne() { sendMessage("command", "enableRepeatOne" ); }
void WebSocket::play()            { sendMessage("command", "play"            ); }
void WebSocket::next()            { sendMessage("command", "next"            ); }
void WebSocket::pause()           { sendMessage("command", "pause"           ); }
void WebSocket::dislikeCurrent()  { sendMessage("command", "dislikeCurrent"  ); }
// clang-format on
