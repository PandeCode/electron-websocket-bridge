#define CROW_MAIN
#define CROW_ENABLE_DEBUG
#include "Log.hpp"
#include "Server.hpp"
#include "crow/app.h"
#include "crow/json.h"

#include <atomic>
#include <cstdlib>
#include <string>
#include <string_view>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <vector>

int main(int argc, char** argv) {

	uint16_t port;
	if(argc > 1)
		port = std::atoi(argv[1]);
	else
		port = 8080;

#	if CMAKE_BUILD_TYPE_RELEASE
	auto logLevel = crow::LogLevel::CRITICAL;
#	else
	auto logLevel = crow::LogLevel::DEBUG;
#endif

	Server server(port, logLevel);
	server.startServer();
}
