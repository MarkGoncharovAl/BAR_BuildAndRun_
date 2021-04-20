#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Help/Picture/Picture.hpp"
#include "../Help/Text/Text.hpp"
#include "../Help/FastDraw.hpp"

namespace sfDATA
{
    class Text_t
    {
    public:
        static bool SetMap (sfC::Window& window);
        static bool AnalyseSetMap (sfC::Window& window);

        static void PrepareData ();
        static std::string WaitTextUser (sfC::Window& window);

        static void CorrectView (sfC::Window& window) { window->setView (view); }

    private:
        static sfC::Text_t main_text;
        static sfC::Text_t addition_text;
        static sf::View view;

        static sfC::Text_t show_down_action1;
        static sfC::Text_t show_down_action2;
    };
}