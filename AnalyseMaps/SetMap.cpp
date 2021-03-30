#include "SetMap.hpp"
#include "../MainMenus/MainMenus.hpp"
#include "AnalyseText.hpp"
#include "MapPrototypes.hpp"

//MainGame_t

sfC::Text_t sfDATA::SetMap_t::main_text ("../Fonts/nfs-mw3.ttf" , 100 , sf::Vector2f (sfCON::WindowWidth * 0.1f , sfCON::WindowHeight * 0.25f) , "Download map");
size_t sfDATA::SetMap_t::cur_map = 0;
sfC::Text_t sfDATA::SetMap_t::cur_text ("../Fonts/19413.ttf" , 200 , sf::Vector2f (sfCON::WindowWidth * 0.1f , sfCON::WindowHeight * 0.5f) , "");
sfC::Picture_t sfDATA::SetMap_t::direct_back ("../Images/direct.png" , sf::IntRect (109 , 22 , -87 , 59) , sf::Vector2f (0.f , 0.f) , sf::Color::White);

void sfDATA::SetMap_t::PrepareData (std::vector<std::string>& maps)
{
    cur_text.set_text (maps.at (cur_map));
    main_text.set_color (sf::Color::Red);
    cur_text.set_color (sf::Color::Red);
}

std::string sfDATA::SetMap_t::GetText ()
{
    return cur_text.get_text ();
}

void sfDATA::SetMap_t::IncreaseMap ()
{
    if (cur_map + 1 < MapPrototypes_t::GetSizeMaps ())
    {
        cur_map += 1;
        cur_text.set_text (MapPrototypes_t::GetNameMap (cur_map));
    }
}

void sfDATA::SetMap_t::DecreaseMap ()
{
    if (cur_map > 0)
    {
        cur_map--;
        cur_text.set_text (MapPrototypes_t::GetNameMap (cur_map));
    }
}

void sfDATA::SetMap_t::DrawEverything (sf::RenderWindow& window)
{
    window.draw (main_text.for_draw ());
    window.draw (cur_text.for_draw ());
    window.draw (direct_back.for_draw ());
}

bool sfDATA::SetMap_t::AnalysePrepareCreateMap (sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent (event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
                sfDATA::Text_t::ShowDoneAction (window , cur_text.get_text () , "selected");
                return false;
            case sf::Keyboard::Right:
                if (cur_map + 1 < sfDATA::MapPrototypes_t::GetSizeMaps ())
                {
                    cur_map += 1;
                    cur_text.set_text (sfDATA::MapPrototypes_t::GetNameMap (cur_map));
                }
                break;
            case sf::Keyboard::Left:
                if (cur_map > 0)
                {
                    cur_map--;
                    cur_text.set_text (sfDATA::MapPrototypes_t::GetNameMap (cur_map));
                }
                break;
            default:
                break;
            }
        }
    }
    return true;
}
void sfDATA::SetMap_t::PrepareCreateMap (sf::RenderWindow& window , sfC::Map& map)
{
    sfDATA::Text_t::CorrectView (window);

    while (window.isOpen ())
    {
        if (!AnalysePrepareCreateMap (window))
            break;

        window.clear ();
        window.draw (sfDATA::Text_t::BackgroundDraw ());
        window.draw (main_text.for_draw ());
        window.draw (cur_text.for_draw ());
        window.display ();
    }

    sfDATA::MainGame_t::read_map (cur_text.get_text () , map);
}