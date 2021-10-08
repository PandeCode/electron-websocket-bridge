#pragma once
#include <iostream>

#define ERROR_COLOR                          "\033[91m"
#define DEBUG_COLOR                          "\033[95m"
#define INFO_COLOR                           "\033[94m"
#define SUCCESS_COLOR                        "\033[92m"
#define WARN_COLOR                           "\033[93m"
#define ENDC                                 "\033[0m"
#define WHITE_COLOR                          "\u001b[37m"

#define STREAM_WRAP_COLOR(TEXT, COLOR)       COLOR << TEXT << ENDC
#define BRACE_WRAP(TEXT)                     WHITE_COLOR << '[' << ENDC << TEXT << WHITE_COLOR << "] " << ENDC
#define STREAM_WRAP_COLOR_BRACE(TEXT, COLOR) BRACE_WRAP(STREAM_WRAP_COLOR(TEXT, COLOR))
#define SWCB STREAM_WRAP_COLOR_BRACE

namespace    Log          {
	template <typename... Args> inline void Info(const    Args&... args) { std::cout << SWCB("INFO   ", INFO_COLOR);    (std::cout << ... << args) << std::endl; }
	template <typename... Args> inline void Error(const   Args&... args) { std::cout << SWCB("ERROR  ", ERROR_COLOR);   (std::cout << ... << args) << std::endl; }
	template <typename... Args> inline void Warn(const    Args&... args) { std::cout << SWCB("WARN   ", WARN_COLOR);    (std::cout << ... << args) << std::endl; }
	template <typename... Args> inline void Debug(const   Args&... args) { std::cout << SWCB("DEBUG  ", DEBUG_COLOR);   (std::cout << ... << args) << std::endl; }
	template <typename... Args> inline void Success(const Args&... args) { std::cout << SWCB("SUCCESS", SUCCESS_COLOR); (std::cout << ... << args) << std::endl; }
}
