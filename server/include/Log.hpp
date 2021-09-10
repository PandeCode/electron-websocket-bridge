#pragma once
#include <iostream>

#define ERROR_COLOR   "\033[91m"
#define DEBUG_COLOR   "\033[95m"
#define INFO_COLOR    "\033[94m"
#define SUCCESS_COLOR "\033[92m"
#define WARN_COLOR    "\033[93m"
#define ENDC          "\033[0m"

namespace Log {
	inline void Info(const std::string& text) {
		std::cout << INFO_COLOR << "INFO:    " << text << ENDC << std::endl;
	}
	inline void Error(const std::string& text) {
		std::cout << ERROR_COLOR << "ERROR:   " << text << ENDC << std::endl;
	}
	inline void Warn(const std::string& text) {
		std::cout << WARN_COLOR << "WARN:    " << text << ENDC << std::endl;
	}
	inline void Debug(const std::string& text) {
		std::cout << DEBUG_COLOR << "DEBUG:   " << text << ENDC << std::endl;
	}
	inline void Success(const std::string& text) {
		std::cout << SUCCESS_COLOR << "SUCCESS: " << text << ENDC << std::endl;
	}
}
