#include "AnalyseText.hpp"
#include "../Help/Help.hpp"
#include "SetMap.hpp"
#include "CreateMap.hpp"
#include "../MainMenus/MainMenus.hpp"

//MainGame 

sfC::Picture_t sfDATA::Text_t::background ("../Images/Saving2.png" , sf::IntRect (0 , 0 , sfCON::WindowWidth , sfCON::WindowHeight) , sf::Vector2f (0.f , 0.f) , sf::Color::Magenta);

sfC::Text_t sfDATA::Text_t::main_text ("../Fonts/nfs-mw3.ttf" , 120 , sf::Vector2f (sfCON::WindowWidth * 0.1f , sfCON::WindowHeight * 0.35f) , "Create map");
sfC::Text_t sfDATA::Text_t::addition_text ("../Fonts/19413.ttf" , 100 , sf::Vector2f (sfCON::WindowWidth * 0.1f , sfCON::WindowHeight * 0.5f) , "NAME: ");

sf::View sfDATA::Text_t::view (sf::FloatRect (0.f , 0.f , sfCON::WindowWidth , sfCON::WindowHeight));

sfC::Text_t sfDATA::Text_t::show_down_action1 ("../Fonts/19413.ttf" , 120 , sf::Vector2f (sfCON::WindowWidth * 0.05f , sfCON::WindowHeight * 0.44f));
sfC::Text_t sfDATA::Text_t::show_down_action2 ("../Fonts/19413.ttf" , 80 , sf::Vector2f (sfCON::WindowWidth * 0.05f , sfCON::WindowHeight * 0.6f));

void sfDATA::Text_t::PrepareData ()
{
    main_text.set_color (sf::Color::Red);
    addition_text.set_color (sf::Color::Red);
    show_down_action1.set_color (sf::Color::Red);
    show_down_action2.set_color (sf::Color::Red);
}

void sfDATA::Text_t::ShowDoneAction (sf::RenderWindow& window , const std::string& info1 , const std::string& info2 /* = std::string()*/)
{
    //background, show_done_action1/2
    constexpr int64_t max_time = 1000000;

    show_down_action1.set_text (info1);
    show_down_action2.set_text (info2);
    sf::Clock clock;
    clock.restart ();

    if (info2.empty ())
    {
        while (window.isOpen () && clock.getElapsedTime ().asMicroseconds () < max_time)
        {

            window.clear ();

            window.draw (background.for_draw ());
            window.draw (show_down_action1.for_draw ());

            window.display ();
        }
    }
    else
    {
        while (window.isOpen () && clock.getElapsedTime ().asMicroseconds () < max_time)
        {

            window.clear ();

            window.draw (background.for_draw ());
            window.draw (show_down_action1.for_draw ());
            window.draw (show_down_action2.for_draw ());

            window.display ();
        }
    }
}

bool sfDATA::Text_t::SetMap (sf::RenderWindow& window)
{
    CorrectView (window);
    while (window.isOpen ())
    {
        if (!AnalyseSetMap (window))
            break;

        window.clear ();
        window.draw (background.for_draw ());
        sfDATA::SetMap_t::DrawEverything (window);
        window.display ();
    }

    return false;
}
bool sfDATA::Text_t::AnalyseSetMap (sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent (event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                ShowDoneAction (window , "Not selected");
                return false;
                break;
            case sf::Keyboard::Enter:
                if (!MainGame_t::read_map (SetMap_t::GetText ()))
                {
                    ShowDoneAction (window , "Not selected!");
                    return true;
                }
                else
                {
                    ShowDoneAction (window , SetMap_t::GetText () , "selected");
                    return false;
                }
                break;
            case sf::Keyboard::Right:
                SetMap_t::IncreaseMap ();
                break;
            case sf::Keyboard::Left:
                SetMap_t::DecreaseMap ();
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left &&
                SetMap_t::IsIncludeDirect (event.mouseButton.x , event.mouseButton.y))
            {
                Text_t::ShowDoneAction (window , "Not selected");
                return false;
            }
        }
    }
    return true;

}

std::string sfDATA::Text_t::WaitTextUser (sf::RenderWindow& window)
{
    std::string text;
    sfC::Text_t user_text ("../Fonts/19413.ttf" , 100 , sf::Vector2f (sfCON::WindowWidth * 0.3f , sfCON::WindowHeight * 0.5f) , "");
    user_text.set_color (sf::Color::Cyan);

    window.setView (view);

    while (window.isOpen ())
    {
        if (!sfF::AnalyseWait_Text_User (window , text , user_text))
            break;

        window.clear (sf::Color::White);
        window.draw (background.for_draw ());
        window.draw (main_text.for_draw ());
        window.draw (addition_text.for_draw ());
        window.draw (user_text.for_draw ());
        window.display ();
    }

    return text;
}