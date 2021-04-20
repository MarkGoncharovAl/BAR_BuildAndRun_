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

void sfDATA::SetMap_t::DrawEverything (sfC::Window& window)
{
    window.AddArgs (main_text , cur_text , direct_back);
}

sfDATA::SetMap_t::OutT sfDATA::SetMap_t::AnalysePrepareCreateMap (sfC::Window& window)
{
    sf::Event event;
    bool anything_done = false;
    while (window->pollEvent (event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
                sfF::ShowDoneAction (window , cur_text.get_text () , "selected");
                return OutT::Exit;
            case sf::Keyboard::Right:
                if (cur_map + 1 < sfDATA::MapPrototypes_t::GetSizeMaps ())
                {
                    anything_done = true;
                    cur_map += 1;
                    cur_text.set_text (sfDATA::MapPrototypes_t::GetNameMap (cur_map));
                }
                break;
            case sf::Keyboard::Left:
                if (cur_map > 0)
                {
                    anything_done = true;
                    cur_map--;
                    cur_text.set_text (sfDATA::MapPrototypes_t::GetNameMap (cur_map));
                }
                break;
            default:
                break;
            }
        }
    }

    if (anything_done)
        return OutT::Changed;
    return OutT::Continue;
}

void sfDATA::SetMap_t::PrepareCreateMap (sfC::Window& window , sfC::Map& map)
{
    sfDATA::Text_t::CorrectView (window);
    window.Draw (sfCON::Saving2PNG , main_text , cur_text);

    std::cout << "A\n";
    while (window->isOpen ())
    {
        switch (AnalysePrepareCreateMap (window))
        {
        case OutT::Changed:
            window.Draw (sfCON::Saving2PNG , main_text , cur_text);
            break;
        case OutT::Continue:
            break;
        case OutT::Error:
            return;
        case OutT::Exit:
            goto exit;
        };
    }

exit:
    sfDATA::MainGame_t::read_map (cur_text.get_text () , map);
}