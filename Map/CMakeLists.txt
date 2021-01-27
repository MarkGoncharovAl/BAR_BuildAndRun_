cmake_minimum_required(VERSION 3.12)
project(Map VERSION 1.0.0)

add_library(
    Map
    Map.hpp
    Map.cpp
)

add_library(
    MapPrototypes
    MapPrototypes.hpp
    MapPrototypes.cpp
)