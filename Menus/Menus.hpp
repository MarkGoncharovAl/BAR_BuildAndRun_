#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <array>
#include <memory>
#include "../Help/Text/Text.hpp"
#include "../Map/Map.hpp"

/////////////////////////////////////////////////////
// Check the user actions in the menu
// Returns false - if it's time to close menu
//         true  - user didn't make a choise
/////////////////////////////////////////////////////
bool AnalyseMenu(sf::RenderWindow &window);

/////////////////////////////////////////////////////
// Create main menu
// Returns false - if menu was closen
//         true  - never now))
/////////////////////////////////////////////////////
bool MainMenu(sf::RenderWindow &window);

/////////////////////////////////////////////////////
// Menu where user can create a car
/////////////////////////////////////////////////////
bool AnalyseMenuCars(sf::RenderWindow &window, int cout_blocks);
/////////////////////////////////////////////////////
// Menu where user can create a car
/////////////////////////////////////////////////////
bool MenuCars(sf::RenderWindow &window);

bool AnalyseWait_Text_User(sf::RenderWindow &window, std::string &text, sfC::Text_t &user_text);
std::string Wait_Text_User(sf::RenderWindow &window);

bool AnalyseSetMap(sf::RenderWindow &window);
bool SetMap(sf::RenderWindow &window);

bool AnalysePrepareCreateMap(sf::RenderWindow &window);
void PrepareCreateMap(sf::RenderWindow &window, sfC::Map &map);

bool AnalyseCreateMap(sf::RenderWindow &window);
bool CreateMap(sf::RenderWindow &window);