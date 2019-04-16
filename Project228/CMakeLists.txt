cmake_minimum_required(VERSION 3.12)
project(Project228)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project228 main.cpp player.cpp player.h main_headers.h functions.h constants.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -IC:/SFML-2.5.1/include -LC:/SFML-2.5.1/lib")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(Project228 sfml-audio sfml-network sfml-graphics sfml-window sfml-system)