cmake_minimum_required(VERSION 3.10)
project(Main VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3") 

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_subdirectory(Common_libs/Errors)
add_subdirectory(Common_libs/Random)
add_subdirectory(Common_libs/Matrix)

add_subdirectory(Help/Text)
add_subdirectory(Help/ParamCar)
add_subdirectory(Help/Direction)
add_subdirectory(Help/Data)
add_subdirectory(Help)
add_subdirectory(Map)
add_subdirectory(Object)
add_subdirectory(Menus)
add_subdirectory(Menus/Main)

message("Building!")
add_executable(
    run
    Main.cpp  
    Actions/Actions.cpp
)

target_link_libraries(
    run 
    
    sfml-graphics 
    sfml-audio 

    Random 
    Errors
    Matrix 

    Menus
    MenusMain

    Map
    MapPrototypes

    Text 
    Help 
    ParamCar
    Direction
    Data
    Object
)
