#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <array>
#include <memory>
#include "../Help/Text/Text.hpp"
#include "../Map/Map.hpp"

bool AnalyseWait_Text_User(sf::RenderWindow &window, std::string &text, sfC::Text_t &user_text);
std::string Wait_Text_User(sf::RenderWindow &window);

bool AnalyseSetMap(sf::RenderWindow &window);
bool SetMap(sf::RenderWindow &window);

bool AnalysePrepareCreateMap(sf::RenderWindow &window);
void PrepareCreateMap(sf::RenderWindow &window, sfC::Map &map);

bool AnalyseCreateMap(sf::RenderWindow &window);
bool CreateMap(sf::RenderWindow &window);