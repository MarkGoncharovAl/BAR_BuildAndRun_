cmake_minimum_required(VERSION 3.12)
project(Main VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3") 

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_subdirectory(Common_libs)
add_subdirectory(Help/Picture)
add_subdirectory(Help/Text)
add_subdirectory(Help/ParamCar)
add_subdirectory(Help)

message("Building!")
add_executable(main Main.cpp Menus/Menus.cpp Map/Map.cpp Help/Data.cpp Actions/Actions.cpp Objects/Tank.cpp)
target_link_libraries(
    main 
    
    sfml-graphics 
    sfml-audio 

    random 
    errors 
    
    Picture 
    Text 
    Help 
    ParamCar
    )
