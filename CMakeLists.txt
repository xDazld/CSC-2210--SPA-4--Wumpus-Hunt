cmake_minimum_required(VERSION 3.28)
project(SPA_4_Wumpus_Hunt)

set(CMAKE_CXX_STANDARD 26)

add_executable(SPA_4_Wumpus_Hunt main.cpp
        Controller.h
        Network.h
        Player.h
        Attack.h
        Defense.h
        Controller.cpp
        Player.cpp
        Network.cpp
        Attack.cpp
        Defense.cpp
        service.cpp
        service.h
)


if (CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -g")
endif ()