project(gui VERSION 1.0 DESCRIPTION "gui Description" LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
set(GUI_PROJECT_LIBRARIES ${CMAKE_THREAD_LIBS_INIT} Qt5::Widgets Qt::Core)

file(GLOB_RECURSE GUI_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
set(GUI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

message("GUI PROJECT")
message("CMAKE_THREAD_LIBS_INIT : " ${CMAKE_THREAD_LIBS_INIT})
message("GUI INCLUDE_DIRS       : " ${GUI_INCLUDE_DIRS})
message("GUI PROJECT_LIBRARIES  : " ${GUI_PROJECT_LIBRARIES})
message("GUI SRC_FILES          : " ${GUI_SRC_FILES})

add_executable(${PROJECT_NAME} ${GUI_SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${GUI_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GUI_PROJECT_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE -pthread)
target_precompile_headers(
  ${PROJECT_NAME} PRIVATE
  <iostream>
  <string>
  <atomic>
  <string_view>
)
 

cotire(${PROJECT_NAME})
