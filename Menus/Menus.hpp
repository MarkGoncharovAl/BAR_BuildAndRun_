#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <array>
#include <memory>
#include "../Help/Data/Data.hpp"
#include "../Help/Text/Text.hpp"
#include "../Help/Picture/Picture.hpp"
#include "../Help/Direction/Direction.hpp"
#include "../Help/ParamCar/ParamCar.hpp"
#include "../Map/Map.hpp"

namespace sfDATA
{

    class MenuCars
    {
    public:
        static bool AnalyseMenuCars(sf::RenderWindow &);
        static bool CheckMenuCars(sf::RenderWindow &window);
        static void prepare_data_MenuCars();

        static void Restart();

    private:
        static sfC::Picture_t main_pic;

        static std::string file_buttons;
        static sf::IntRect tex_rect;

        static std::array<sfC::Picture_t, 4> main_buttons;

        static std::array<sfC::Picture_t, 8> buttons;
        static std::array<sfC::Text_t, 6> texts;

        static std::array<sfC::Text_t, 8> levels;

        static sfC::Picture_t car1;
        static sfC::Picture_t car2;
        static sfC::MenuCars_t data;

        static sfC::ParamCar_t sort1;
        static sfC::ParamCar_t sort2;
    };

} // namespace sfDATA

bool AnalyseWait_Text_User(sf::RenderWindow &window, std::string &text, sfC::Text_t &user_text);
std::string Wait_Text_User(sf::RenderWindow &window);

bool AnalyseSetMap(sf::RenderWindow &window);
bool SetMap(sf::RenderWindow &window);

bool AnalysePrepareCreateMap(sf::RenderWindow &window);
void PrepareCreateMap(sf::RenderWindow &window, sfC::Map &map);

bool AnalyseCreateMap(sf::RenderWindow &window);
bool CreateMap(sf::RenderWindow &window);