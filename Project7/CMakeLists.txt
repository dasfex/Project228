cmake_minimum_required(VERSION 3.12)
project(NewProject228)

set(CMAKE_CXX_STANDARD 17)

add_executable(NewProject228 Source.cpp player.cpp player.h main_headers.h
        functions.h constants.h quest_hero.cpp quest_hero.h useful.h
        draw.h bullet.h bullet.cpp enemy.cpp enemy.h menu.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ID:/SFML-2.5.1/include -LD:/SFML-2.5.1/lib")

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(NewProject228 sfml-audio
        sfml-network sfml-graphics sfml-window sfml-system)