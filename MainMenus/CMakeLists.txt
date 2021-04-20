cmake_minimum_required(VERSION 3.10)
project(MainMaps VERSION 1.0.0)

add_library(
    MainMenus
    MainMenus.hpp
    MainMenus.cpp
)

add_library(
    ServerGame
    Server.hpp
    ServerGame.hpp
    ServerGame.cpp
    Server.cpp
)