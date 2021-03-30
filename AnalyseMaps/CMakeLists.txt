cmake_minimum_required(VERSION 3.10)
project(SetMap VERSION 1.0.0)

add_library(
    SetMap
    SetMap.hpp
    SetMap.cpp
)

add_library(
    AnalyseText
    AnalyseText.cpp
    AnalyseText.hpp
)

add_library(
    AnalyseMapPrototypes
    MapPrototypes.hpp
    MapPrototypes.cpp
)

add_library(
    CreateMap
    CreateMap.hpp
    CreateMap.cpp
)