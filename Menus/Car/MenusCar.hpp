#pragma once

#include <iostream>
#include "../../Help/Picture/Picture.hpp"
#include "../../Help/Text/Text.hpp"
#include "../../Help/ParamCar/ParamCar.hpp"

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
