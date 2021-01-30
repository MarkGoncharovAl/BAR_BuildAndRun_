#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../Help/Picture/Picture.hpp"
#include "../../Help/Text/Text.hpp"

namespace sfDATA
{

    class MainMenu
    {
    public:
        /////////////////////////////////////////////////////
        // Check the user actions in the menu
        // Returns false - if it's time to close menu
        //         true  - user didn't make a choise
        /////////////////////////////////////////////////////
        static bool AnalyseMenu(sf::RenderWindow &window);

        /////////////////////////////////////////////////////
        // Create main menu
        // Returns false - if menu was closen
        //         true  - never now))
        /////////////////////////////////////////////////////
        static bool ChechMainMenu(sf::RenderWindow &window);

        static void prepare_data_main_menu();

    private:
        static sf::IntRect released_;
        static sf::IntRect pressed_;

        static constexpr int count_buttons_ = 5;
        enum type_button_ : int
        {
            GAME = 0,
            RESTART,
            SET,
            CREATE,
            EXIT
        };
        static int cur_press_;

        static sfC::Picture_t main_pic_;

        static std::array<sfC::Picture_t, count_buttons_> buttons_;
        static std::array<sfC::Text_t, count_buttons_> texts_;

        /////////////////////
        // Returns false if function should be ended
        // if (!ActionPress(...)) return ...
        /////////////////////
        static bool ActionPress(sf::RenderWindow &window, int press);
        static void Full_Restart();
    };

} // namespace sfDATA