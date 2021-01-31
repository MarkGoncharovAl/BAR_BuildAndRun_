cmake_minimum_required(VERSION 3.10)
project(Lib VERSION 1.0.0)

set(iterators iterators.hpp)

add_library(
    errors
    errors.hpp
    errors.cpp
)

add_library(
    random
    random.hpp
    random.cpp
)
