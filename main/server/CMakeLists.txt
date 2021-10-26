project(server VERSION 1.0 DESCRIPTION "server Description" LANGUAGES CXX)

if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_compile_definitions(CMAKE_BUILD_TYPE_RELEASE=1)
else()
  add_compile_definitions(CMAKE_BUILD_TYPE_RELEASE=0)
endif()

file(GLOB_RECURSE SERVER_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
set(SERVER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SERVER_PROJECT_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

message("SERVER PROJECT")
message("CMAKE_THREAD_LIBS_INIT : " ${CMAKE_THREAD_LIBS_INIT})
message("INCLUDE_DIRS           : " ${INCLUDE_DIRS})
message("PROJECT_LIBRARIES      : " ${PROJECT_LIBRARIES})
message("SRC_FILES              : " ${SRC_FILES})

add_executable(${PROJECT_NAME} ${SERVER_SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${SERVER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SERVER_PROJECT_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE -pthread)
target_precompile_headers(
  ${PROJECT_NAME} PRIVATE
  <iostream>
  <string>
  <atomic>
  <string_view>
)

cotire(${PROJECT_NAME})
