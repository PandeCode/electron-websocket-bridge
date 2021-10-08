cmake_minimum_required(VERSION 3.20)

set(CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS ON)

set(CMAKE_C_COMPILER /usr/bin/clang CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE PATH "" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++2b -fuse-ld=lld -Wno-unused-command-line-argument") # -v

# cmake-format: off
set(CMAKE_C_FLAGS_INIT "-Wall")
set(CMAKE_C_FLAGS_DEBUG_INIT "-g")
set(CMAKE_C_FLAGS_MINSIZEREL_INIT "-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE_INIT "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")
set(CMAKE_CXX_FLAGS_INIT "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL_INIT "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")
# cmake-format: on

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_compile_definitions(CMAKE_BUILD_TYPE_RELEASE=1)
else()
  add_compile_definitions(CMAKE_BUILD_TYPE_RELEASE=0)
endif()

project(server VERSION 1.0 DESCRIPTION "server Description" LANGUAGES CXX)

find_package(Threads REQUIRED)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LINK_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(PROJECT_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

message("CMAKE_THREAD_LIBS_INIT : " ${CMAKE_THREAD_LIBS_INIT})
message("INCLUDE_DIRS           : " ${INCLUDE_DIRS})
message("LINK_DIRS              : " ${LINK_DIRS})
message("PROJECT_LIBRARIES      : " ${PROJECT_LIBRARIES})
message("SRC_FILES              : " ${SRC_FILES})

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${LINK_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE -pthread)
target_precompile_headers(
  ${PROJECT_NAME} PRIVATE
  <iostream>
  <string>
  <atomic>
  <string_view>
)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")
include(cotire)
cotire(${PROJECT_NAME})
