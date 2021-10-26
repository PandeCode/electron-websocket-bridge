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
#define SWCB                                 std::cout << STREAM_WRAP_COLOR_BRACE
#define VAR_COUT                             (std::cout << ... << args) << std::endl
#define DEF_LOG(NAME, STRING, COLOR)            \
	template <typename... Args>             \
	inline void NAME(const Args&... args) { \
		SWCB(STRING, COLOR);            \
		VAR_COUT;                       \
	}

namespace Log {
	// clang-format off
	DEF_LOG(Info,    " INFO  ", INFO_COLOR);
	DEF_LOG(Error,   " ERROR ", ERROR_COLOR);
	DEF_LOG(Warn,    " WARN  ", WARN_COLOR);
	DEF_LOG(Debug,   " DEBUG ", DEBUG_COLOR);
	DEF_LOG(Success, "SUCCESS", SUCCESS_COLOR);
	// clang-format on
}
