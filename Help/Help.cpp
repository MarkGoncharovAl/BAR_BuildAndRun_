#include "Help.hpp"

namespace sfF
{
    bool IS_ASKII (const sf::Uint32& symbol) noexcept
    {
        return (symbol > 47 && symbol < 58) ||
            (symbol > 64 && symbol < 91) ||
            (symbol > 96 && symbol < 123) ||
            symbol == 95;
    }

    bool change_text_num (sfC::Text_t& str , int dist)
    {
        str.set_text (std::to_string (stoi (str.get_text ()) + dist));
        if (str.get_text ().empty ())
            return false;
        return true;
    }

    bool change_text_num (std::string& str , int dist)
    {
        str = std::to_string (stoi (str) + dist);
        if (str.empty ())
            return false;
        return true;
    }

    sf::Vector2f get_view_position (const sf::View& view)
    {
        return sf::Vector2f (view.getCenter ().x - view.getSize ().x / 2.f ,
                            view.getCenter ().y - view.getSize ().y / 2.f);
    }

    float get_view_position_x (const sf::View& view)
    {
        return view.getCenter ().x - view.getSize ().x / 2.f;
    }

    float get_view_position_y (const sf::View& view)
    {
        return view.getCenter ().y - view.getSize ().y / 2.f;
    }

    bool AnalyseWait_Text_User (sfC::Window& window , std::string& text , sfC::Text_t& user_text)
    {
        sf::Event event;
        while (window->pollEvent (event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    text.clear ();
                    return false;
                    break;
                case sf::Keyboard::Enter:
                    return false;
                    break;
                case sf::Keyboard::BackSpace:
                case sf::Keyboard::Delete:
                    text.pop_back ();
                    user_text.pop_back ();
                    break;
                default:
                    break;
                }
            }

            if (event.type == sf::Event::TextEntered)
            {
                if (sfF::IS_ASKII (event.text.unicode))
                {
                    char cur_symbol = static_cast<char>(event.text.unicode);
                    text.push_back (cur_symbol);
                    user_text.push_back (cur_symbol);
                }
            }
        }
        return true;
    }

    void SetDefaultView (sfC::Window& window)
    {
        window->setView (sf::View (sf::FloatRect { 0.f, 0.f, sfCON::WindowWidth , sfCON::WindowHeight }));
    }

    void ShowDoneAction (sfC::Window& window , std::string const& text1 , std::string const& text2 /*= ""*/)
    {
        //background, show_done_action1/2
        constexpr int64_t max_time = 1000000;

        sfC::Text_t show_down_action1 (sfCON_FILE_FontDigit_ttf , 120 , sf::Vector2f (sfCON::WindowWidth * 0.05f , sfCON::WindowHeight * 0.44f));
        sfC::Text_t show_down_action2 (sfCON_FILE_FontDigit_ttf , 80 , sf::Vector2f (sfCON::WindowWidth * 0.05f , sfCON::WindowHeight * 0.6f));
        show_down_action1.set_text (text1);
        show_down_action2.set_text (text2);

        sf::Clock clock;
        clock.restart ();

        if (text2.empty ())
        {
            while (window->isOpen () && clock.getElapsedTime ().asMicroseconds () < max_time)
                window.Draw (sfCON::Saving2PNG , show_down_action1);
        }
        else
        {
            while (window->isOpen () && clock.getElapsedTime ().asMicroseconds () < max_time)
                window.Draw (sfCON::Saving2PNG , show_down_action1 , show_down_action2);
        }
    }
} // namespace sfF