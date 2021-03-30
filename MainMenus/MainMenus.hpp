#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <stack>
#include "../Map/Map.hpp"
#include "../Object/Object.hpp"
#include "../Help/Picture/Picture.hpp"
#include "../Help/Help.hpp"
#include "../Help/Direction/Direction.hpp"

namespace sfDATA
{
    //!Common functions!
    ////////////////////////////////////////////////////////////
    void Full_Restart ();
    void PrepareData ();
    ////////////////////////////////////////////////////////////

    class MainMenu_t
    {
    public:
        /////////////////////////////////////////////////////
        // Check the user actions in the menu
        // Returns false - if it's time to close menu
        //         true  - user didn't make a choise
        /////////////////////////////////////////////////////
        static bool AnalyseMenu (sf::RenderWindow& window);

        /////////////////////////////////////////////////////
        // Create main menu
        // Returns false - if menu was closen
        //         true  - never now))
        /////////////////////////////////////////////////////
        static bool MainMenu (sf::RenderWindow& window);

        static void PrepareData ();

    private:
        static sf::IntRect released_;
        static sf::IntRect pressed_;

        static constexpr int count_buttons_ = 5;
        enum type_button_ : int
        {
            GAME = 0 ,
            RESTART ,
            SET ,
            CREATE ,
            EXIT
        };
        static int cur_press_;

        static sfC::Picture_t main_pic_;

        static std::array<sfC::Picture_t , count_buttons_> buttons_;
        static std::array<sfC::Text_t , count_buttons_> texts_;

        /////////////////////
        // Returns false if function should be ended
        // if (!ActionPress(...)) return ...
        /////////////////////
        static bool ActionPress (sf::RenderWindow& window , int press);
    };

} // namespace sfDATA

namespace sfDATA
{

    class MenuCars_t
    {
    public:
        static void Restart ();
        /////////////////////////////////////////////////////
        // Menu where user can create a car
        /////////////////////////////////////////////////////
        static bool AnalyseMenuCars (sf::RenderWindow&);
        /////////////////////////////////////////////////////
        // Menu where user can create a car
        /////////////////////////////////////////////////////
        static bool MenuCars (sf::RenderWindow& window);

        static void PrepareData ();

    private:
        static sfC::Picture_t main_pic;

        static std::string file_buttons;
        static sf::IntRect tex_rect;

        static std::array<sfC::Picture_t , 4> main_buttons;

        static std::array<sfC::Picture_t , 8> buttons;
        static std::array<sfC::Text_t , 6> texts;

        static std::array<sfC::Text_t , 8> levels;

        static sfC::Picture_t car1;
        static sfC::Picture_t car2;
        static sfC::MenuCars_t data;

        static sfC::ParamCar_t sort1;
        static sfC::ParamCar_t sort2;
    };

    class MainGame_t
    {
    public:
        static void Restart ();
        static void PrepareData (sfC::Map& create_map);
        /////////////////////////////////////////////////////
        // Check the user actions in the game
        // Returns false - if game was closen or ended
        //         true  - game is working now
        /////////////////////////////////////////////////////
        static bool AnalyseGame (sf::RenderWindow& window , float time);
        /////////////////////////////////////////////////////
        // Create the game
        // Returns false - if game was closen or ended
        //         true  - never now))
        /////////////////////////////////////////////////////
        static bool MainGame (sf::RenderWindow& window , const sfC::ParamCar_t& sort1 , const sfC::ParamCar_t& sort2);
        /////////////////////////////////////////////////////
        // Check: user reached the goal or not
        // Return false - if game isn't over
        //        true  - target was achieved
        /////////////////////////////////////////////////////
        static bool CheckWin ();

        //////////////////////
        //returns true if map was read succesfully
        //false in another case
        //////////////////////
        static bool read_map (const std::string& file , sfC::Map& cur_map = sfDATA::MainGame_t::map);

    private:
        static std::array<sfC::Text_t , 4> texts;

        static sfC::Picture_t mid_strip;

        static sf::View view1;
        static sf::View view2;
        static sf::View full_view;

        static sfC::Map map;

        static sfC::Car_t tank1;
        static sfC::Car_t tank2;
    };

} // namespace sfDATA