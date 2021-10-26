#include "../src/mainwindow.cpp"
#include "gui/WebSocket.hpp"


class UIMainWindow : public Ui_MainWindow {
      public:
	WebSocket websocket;

	void init();

	inline void appendRestConsole(const char* message);
	inline void appendWebSocketConsole(const char* message);
	inline void appendRestConsole(const std::string& message);
	inline void appendWebSocketConsole(const std::string& message);

	inline void deactivateWebSocket();

	inline void activateWebSocket();

	~UIMainWindow();
};
