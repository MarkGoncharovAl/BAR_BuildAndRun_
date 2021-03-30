#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Help/Picture/Picture.hpp"
#include "../Help/Text/Text.hpp"

namespace sfDATA
{
    class Text_t
    {
    public:
        static bool SetMap (sf::RenderWindow& window);
        static bool AnalyseSetMap (sf::RenderWindow& window);

        static void PrepareData ();
        static std::string WaitTextUser (sf::RenderWindow& window);
        static void ShowDoneAction (sf::RenderWindow& window , const std::string& info , const std::string& info2 = std::string ());

        static void CorrectView (sf::RenderWindow& window) { window.setView (view); }
        static const sf::Sprite& BackgroundDraw () { return background.for_draw (); }

    private:
        static sfC::Picture_t background;
        static sfC::Text_t main_text;
        static sfC::Text_t addition_text;
        static sf::View view;

        static sfC::Text_t show_down_action1;
        static sfC::Text_t show_down_action2;
    };
}