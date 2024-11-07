cmake_minimum_required(VERSION 3.28)
project(SPA_4_Wumpus_Hunt)

set(CMAKE_CXX_STANDARD 26)

add_executable(SPA_4_Wumpus_Hunt main.cpp
        Controller.h
        Network.h
        Player.h
        WumpDB.h
        Attack.h
        Defense.h
        Controller.cpp
        Player.cpp
        Network.cpp
        Attack.cpp)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -g -O1")
endif ()