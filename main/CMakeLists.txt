cmake_minimum_required(VERSION 3.20)

set(CXX_STANDARD          20)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS        ON)

set(CMAKE_C_COMPILER   /usr/bin/clang   CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE PATH "" FORCE)
set(CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} -std=gnu++20 -fuse-ld=lld -Wno-unused-command-line-argument")

# cmake-format: off
set(CMAKE_C_FLAGS_INIT                  "-Wall")
set(CMAKE_C_FLAGS_DEBUG_INIT            "-g")
set(CMAKE_C_FLAGS_MINSIZEREL_INIT       "-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE_INIT          "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT   "-O2 -g")
set(CMAKE_CXX_FLAGS_INIT                "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")
# cmake-format: on

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

find_package(Threads REQUIRED)
message("CMAKE_THREAD_LIBS_INIT : " ${CMAKE_THREAD_LIBS_INIT})

include_directories(${CMAKE_SOURCE_DIR}/include)
include(cotire)

add_subdirectory(${CMAKE_SOURCE_DIR}/server)
add_subdirectory(${CMAKE_SOURCE_DIR}/gui)
