#pragma once
#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Server.hpp"
#include "../Map/MapPrototypes.hpp"
#include "../Map/Map.hpp"
#include "../Help/Help.hpp"
#include "../Object/Object.hpp"

namespace sfDATA
{
    class NetworkGame final
    {
    public:
        NetworkGame (sfC::Window& win);
        ~NetworkGame ();

        void Restart ();
        /////////////////////////////////////////////////////
        // Check the user actions in the game
        // Returns false - if game was closen or ended
        //         true  - game is working now
        /////////////////////////////////////////////////////
        enum class OutT { Back , Continue , Error };
        OutT AnalyseGame (float time);
        /////////////////////////////////////////////////////
        // Create the game
        // Returns false - if game was closen or ended
        //         true  - never now))
        /////////////////////////////////////////////////////
        bool Start (const sfC::ParamCar_t& sort1);
        /////////////////////////////////////////////////////
        // Check: user reached the goal or not
        // Return false - if game isn't over
        //        true  - target was achieved
        /////////////////////////////////////////////////////
        bool CheckWin ();
        //////////////////////
        //returns true if map was read succesfully
        //false in another case
        //////////////////////
        bool read_map (const std::string& file , sfC::Map& cur_map);

    private:
        sfC::Window& window;
        std::array<sfC::Text_t , 4> texts;

        sf::View full_view;

        sfC::Map map;

        sfC::Car_t tank1;
        sfC::Picture_t tank2;

    };
}