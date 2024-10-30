cmake_minimum_required(VERSION 3.28)
project(SPA_4_Wumpus_Hunt)

set(CMAKE_CXX_STANDARD 26)

add_executable(SPA_4_Wumpus_Hunt main.cpp
        Controller.h
        Network.h
        Player.h
        WumpDB.h
        Attack.h
        Defense.h)
