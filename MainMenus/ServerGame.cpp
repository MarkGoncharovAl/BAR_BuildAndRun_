#include "ServerGame.hpp"
namespace sfDATA
{
    NetworkGame::NetworkGame (sfC::Window& win) :
        window (win) ,
        texts { sfC::Text_t (sfCON_FILE_Fonts_ttf , 35 , sf::Vector2f (sfCON::WindowWidth * 0.508f , 30.f) , "First car ") ,
                sfC::Text_t (sfCON_FILE_Fonts_ttf , 35 , sf::Vector2f (sfCON::WindowWidth * 0.540f , 65.f) , "0") ,
                sfC::Text_t (sfCON_FILE_Fonts_ttf , 35 , sf::Vector2f (sfCON::WindowWidth * 0.39f , 30.f) , "Second car ") ,
                sfC::Text_t (sfCON_FILE_Fonts_ttf , 35 , sf::Vector2f (sfCON::WindowWidth * 0.422f , 65.f) , "0") } ,
        full_view (sf::FloatRect (0 , 0 , sfCON::WindowWidth , sfCON::WindowHeight)) ,
        map (sfCON_FILE_Blocks_Map) ,
        tank1 (&map , sfCON_FILE_Image_Car , sf::IntRect (93 , 268 , 44 , 78) , sf::Vector2f (80.f , 80.f) , sf::Color (255 , 255 , 255) , 0.7f) ,
        tank2 (sfCON_FILE_Image_Car , sf::IntRect (93 , 138 , 44 , 78) , sf::Vector2f (80.f , 80.f) , sf::Color (255 , 255 , 255) , sf::Vector2f (0.7f , 0.7f))
    {
        sfF::SetDefaultView (window);
        read_map ("Begin" , map);

        for (auto& text : texts)
            text.set_color (sf::Color::Blue);

        tank1.rotate (180.f);
        tank2.rotate (180.f);

        tank1.set_view (&full_view);
        tank2.set_origin (tank1.get_loc_boundaries ().width / 2.f , tank1.get_loc_boundaries ().height / 2.f);
        LOG_trace << "Network game was prepared!";
    }

    NetworkGame::~NetworkGame()
    {
        sfF::SetDefaultView (window); 
        sfF::ShowDoneAction(window, "Closing server");
    }

    NetworkGame::OutT NetworkGame::AnalyseGame (float time)
    {
        if (CheckWin ())
            return OutT::Continue;

        sf::Event event;
        sfC::Direction_t moving_tank1;

        while (window->pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                return OutT::Error;

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                sfF::SetDefaultView (window);
                return OutT::Back;
            }
            moving_tank1.CheckKeyboard (event.type , event.key.code , sfC::Direction_t::Type::Arrows);
        }

        tank1.move_car (moving_tank1 , time);//NEED TANK1

        return OutT::Continue;
    }

    bool sfDATA::NetworkGame::Start (const sfC::ParamCar_t& sort1)
    {
        auto&& socket = Network {}.Start (window);
        std::cout << socket->WhoAmI () << "\n";
        tank1.set_sort (sort1);//NEED TANK

        sf::Clock clock;
        float time = 0;

        sfC::Window draw_window { window };

        while (window->isOpen ())
        {
            time = static_cast<float>(clock.getElapsedTime ().asMicroseconds () / 800.0);
            clock.restart ();

            switch (sfDATA::NetworkGame::AnalyseGame (time))
            {
            case OutT::Back:
                return true;
            case OutT::Error:
                window->close ();
                return false;
            case OutT::Continue:
                break;
            };

            if (!socket->Message (tank2 , tank1.get_position () , tank1.get_rotate ()))
            {
                sfF::SetDefaultView(window);
                sfF::ShowDoneAction (window , "Opponent was exited");
                return true;
            }

            //first player
            window->setView (full_view);
            draw_window.Draw (map , tank1 , tank2 , texts);
        }

        return false;
    }

    bool sfDATA::NetworkGame::CheckWin ()
    {
        //map, tank1, tank2, tests[1], textx[3]
        if (map.is_finish (std::move (tank1.get_boundaries ())))
        {
            if (!sfF::change_text_num (texts[1] , 1))
            {
                LOG_error << "Can't change text";
                exit (EXIT_FAILURE);
            }

            tank1.restart ();
        }

        return false;
    }

    bool sfDATA::NetworkGame::read_map (const std::string& name , sfC::Map& cur_map)
    {
        if (name.empty ())
            return false;

        std::ifstream file ("../MapTiles/" + name + ".txt" , std::ios::in);
        if (!file.is_open ())
            return false;

        sf::Vector2i count_blocks , total_size , block_size;
        file >> count_blocks.x >> count_blocks.y >> total_size.x >> total_size.y >> block_size.x >> block_size.y;

        Matrix_t<int> arr (count_blocks.x , count_blocks.y);
        file >> arr;

        cur_map.create_map (sfC::MapPrototype (count_blocks , block_size , arr));
        return true;
    }

    void sfDATA::NetworkGame::Restart ()
    {
        sfF::RestartCar (tank1);

        texts[1].set_text ("0");
        texts[3].set_text ("0");
    }
    //--------------------------------------
}