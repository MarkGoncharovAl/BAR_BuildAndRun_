#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <array>
#include <memory>
#include "../Menus/Menus.hpp"
#include "../Map/Map.hpp"
#include "../Object/Object.hpp"
#include "../Help/Help.hpp"
#include "../Help/Data/Data.hpp"
#include "../Common_libs/Errors/Errors.hpp"

void Full_Restart();

/////////////////////////////////////////////////////
// Check the user actions in the game
// Returns false - if game was closen or ended
//         true  - game is working now
/////////////////////////////////////////////////////
bool AnalyseGame(sf::RenderWindow &window, float time);

/////////////////////////////////////////////////////
// Create the game
// Returns false - if game was closen or ended
//         true  - never now))
/////////////////////////////////////////////////////
bool MainGame(sf::RenderWindow &window, const sfC::ParamCar_t &sort1, const sfC::ParamCar_t &sort2);

/////////////////////////////////////////////////////
// Check: user reached the goal or not
// Return false - if game isn't over
//        true  - target was achieved
/////////////////////////////////////////////////////
bool CheckWin();

/////////////////////////////////////////////////////
// Reset map
// Count_blocks - how many solid blocks your map will have
/////////////////////////////////////////////////////

void change_data_cars(sfC::ParamCar_t &sort, int proper, sfC::ParamCar_t::Do action = sfC::ParamCar_t::Do::Increase);

void ShowDoneAction(sf::RenderWindow &window, const std::string &info, const std::string &info2 = std::string());
