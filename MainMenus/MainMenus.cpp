#include "MainMenus.hpp"
#include "../Common_libs/Errors/Errors.hpp"
#include "../AnalyseMaps/SetMap.hpp"
#include "../AnalyseMaps/AnalyseText.hpp"
#include "../AnalyseMaps/MapPrototypes.hpp"
#include "../AnalyseMaps/CreateMap.hpp"

namespace sfDATA
{
    void Full_Restart ()
    {
        MenuCars_t::Restart ();
        MainGame_t::Restart ();
    }

    void PrepareData ()
    {
        MainMenu_t::PrepareData ();
        CreateMap_t::PrepareData ();
        MenuCars_t::PrepareData ();
        MapPrototypes_t::PrepareData ();
        Text_t::PrepareData ();
    }

} // namespace sfDATA

//data::menu_cars
//**************************************
sfC::Picture_t sfDATA::MenuCars_t::main_pic ("../Images/menu3.png" , sf::IntRect (0 , 0 , sfCON::WindowWidth , sfCON::WindowHeight) , sf::Vector2f (0 , 0));

std::string sfDATA::MenuCars_t::file_buttons ("../Images/buttons2.png");
sf::IntRect sfDATA::MenuCars_t::tex_rect (32 , 498 , 198 , 64);

std::array<sfC::Picture_t , 4> sfDATA::MenuCars_t::main_buttons = {
    sfC::Picture_t (sfDATA::MenuCars_t::file_buttons, sf::IntRect (32, 377, 198, 64), sf::Vector2f (sfCON::WindowWidth / 2.2f - 15.f, sfCON::WindowHeight / 10.f), sf::Color (sf::Color::White)),
    sfC::Picture_t (sfDATA::MenuCars_t::file_buttons, sf::IntRect (32, 377, 198, 64), sf::Vector2f (sfCON::WindowWidth / 2.2f - 15.f, sfCON::WindowHeight / 6.f), sf::Color (sf::Color::White)),
    sfC::Picture_t ("../Images/direction.png", sf::IntRect (40, 133, 1231, 1037), sf::Vector2f (30.f, 620.f), sf::Color (sf::Color::White), sf::Vector2f (0.05f, 0.05f)),
    sfC::Picture_t ("../Images/direction.png", sf::IntRect (1271, 133, -1231, 1037), sf::Vector2f (1793.f, 620.f), sf::Color (sf::Color::White), sf::Vector2f (0.05f, 0.05f)),
};

std::array<sfC::Picture_t , 8> sfDATA::MenuCars_t::buttons = {
    sfC::Picture_t (sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f (sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f), sf::Color (255, 255, 255)),
    sfC::Picture_t (sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f (sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f + 100), sf::Color (255, 255, 255)),
    sfC::Picture_t (sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f (sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f + 200), sf::Color (255, 255, 255)),
    sfC::Picture_t (sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f (sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f + 300), sf::Color (255, 255, 255)),
    sfC::Picture_t (sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f (sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f), sf::Color (255, 255, 255)),
    sfC::Picture_t (sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f (sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f + 100), sf::Color (255, 255, 255)),
    sfC::Picture_t (sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f (sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f + 200), sf::Color (255, 255, 255)),
    sfC::Picture_t (sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f (sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f + 300), sf::Color (255, 255, 255)),
};
std::array<sfC::Text_t , 6> sfDATA::MenuCars_t::texts = {
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f (sfCON::WindowWidth / 3 + 100, sfCON::WindowHeight / 1.8f + 10), "Acceleration"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f (sfCON::WindowWidth / 3 + 150, sfCON::WindowHeight / 1.8f + 110), "Max speed"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f (sfCON::WindowWidth / 3 + 80, sfCON::WindowHeight / 1.8f + 210), "Rotate speed"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f (sfCON::WindowWidth / 3 + 170, sfCON::WindowHeight / 1.8f + 310), "Controll"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 45, sf::Vector2f (sfCON::WindowWidth / 2.1f - 25.f, sfCON::WindowHeight / 9.7f), "PLAY"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 45, sf::Vector2f (sfCON::WindowWidth / 2.1f - 25.f, sfCON::WindowHeight / 5.8f), "EXIT") };

std::array<sfC::Text_t , 8> sfDATA::MenuCars_t::levels = {
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f (sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 10), "0"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f (sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 110), "0"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f (sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 210), "0"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f (sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 310), "0"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f (sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 10), "0"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f (sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 110), "0"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f (sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 210), "0"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f (sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 310), "0") };

sfC::Picture_t sfDATA::MenuCars_t::car1 ("../Images/cars.png" , sf::IntRect (93 , 268 , 44 , 78) , sf::Vector2f (1640.f , 150.f) , sf::Color (255 , 255 , 255) , sf::Vector2f (2.f , 2.f));
sfC::Picture_t sfDATA::MenuCars_t::car2 ("../Images/cars.png" , sf::IntRect (93 , 138 , 44 , 78) , sf::Vector2f (260.f , 150.f) , sf::Color (255 , 255 , 255) , sf::Vector2f (2.f , 2.f));
sfC::MenuCars_t sfDATA::MenuCars_t::data;

sfC::ParamCar_t sfDATA::MenuCars_t::sort1 = sfCON::sort_tank_BASE;
sfC::ParamCar_t sfDATA::MenuCars_t::sort2 = sfCON::sort_tank_BASE;

void sfDATA::MenuCars_t::Restart ()
{
    data.restart ();
    main_buttons[2].set_position (30.f , 620.f);
    main_buttons[3].set_position (1793.f , 620.f);

    sort1 = sfCON::sort_tank_BASE;
    sort2 = sfCON::sort_tank_BASE;

    for (auto& text : levels)
        text.set_text ("0");
}

bool sfDATA::MenuCars_t::AnalyseMenuCars (sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent (event))
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (main_buttons[0].get_glob_bounds ().contains (static_cast<float>(event.mouseButton.x) , static_cast<float>(event.mouseButton.y)))
                {
                    MainGame_t::MainGame (window , sort1 , sort2);
                    return false;
                }
                if (main_buttons[1].get_glob_bounds ().contains (static_cast<float>(event.mouseButton.x) , static_cast<float>(event.mouseButton.y)))
                {
                    sfDATA::MainMenu_t::MainMenu (window);
                    return false;
                }
            }
        }
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::S:
                if (data.pos_left != 3)
                {
                    data.pos_left++;
                    main_buttons[2].move (0.f , 100.f);
                }
                break;
            case sf::Keyboard::W:
                if (data.pos_left != 0)
                {
                    data.pos_left--;
                    main_buttons[2].move (0.f , -100.f);
                }
                break;
            case sf::Keyboard::D:
                if (data.lvl_left[data.pos_left] != sfCON::levels_char)
                {
                    data.lvl_left[data.pos_left]++;
                    sort2.CorrectProperties (data.pos_left , sfC::ParamCar_t::Do::Increase);

                    if (!sfF::change_text_num (levels[data.pos_left] , 1))
                        ERROR ("Can't change num");
                }
                break;
            case sf::Keyboard::A:
                if (data.lvl_left[data.pos_left] != 0)
                {
                    data.lvl_left[data.pos_left]--;
                    sort2.CorrectProperties (data.pos_left , sfC::ParamCar_t::Do::Decrease);

                    if (!sfF::change_text_num (levels[data.pos_left] , -1))
                        ERROR ("Can't change num");
                }
                break;
            case sf::Keyboard::Down:
                if (data.pos_right != 3)
                {
                    data.pos_right++;
                    main_buttons[3].move (0.f , 100.f);
                }
                break;
            case sf::Keyboard::Up:
                if (data.pos_right != 0)
                {
                    data.pos_right--;
                    main_buttons[3].move (0.f , -100.f);
                }
                break;
            case sf::Keyboard::Right:
                if (data.lvl_right[data.pos_right] != sfCON::levels_char)
                {
                    data.lvl_right[data.pos_right]++;
                    sort1.CorrectProperties (data.pos_right , sfC::ParamCar_t::Do::Increase);

                    if (!sfF::change_text_num (levels[4 + data.pos_right] , 1))
                        ERROR ("Can't change num");
                }
                break;
            case sf::Keyboard::Left:
                if (data.lvl_right[data.pos_right] != 0)
                {
                    data.lvl_right[data.pos_right]--;
                    sort1.CorrectProperties (data.pos_right , sfC::ParamCar_t::Do::Decrease);

                    if (!sfF::change_text_num (levels[4 + data.pos_right] , -1))
                        ERROR ("Can't change num");
                }
                break;
            case sf::Keyboard::Enter:
                MainGame_t::MainGame (window , sort1 , sort2);
                return false;
            case sf::Keyboard::Escape:
                sfDATA::MainMenu_t::MainMenu (window);
                return false;
            default:
                break;
            }
        }
    }

    return true;
}

bool sfDATA::MenuCars_t::MenuCars (sf::RenderWindow& window)
{
    while (window.isOpen ())
    {
        if (!AnalyseMenuCars (window))
            break;

        window.clear ();
        window.draw (main_pic.for_draw ());

        window.draw (car1.for_draw ());
        window.draw (car2.for_draw ());
        car1.rotate (0.2f);
        car2.rotate (0.2f);

        for (const auto& button : main_buttons)
            window.draw (button.for_draw ());

        for (const auto& pic : buttons)
            window.draw (pic.for_draw ());

        for (const auto& text : texts)
            window.draw (text.for_draw ());

        for (const auto& level : levels)
            window.draw (level.for_draw ());

        window.display ();
    }

    return false;
}

void sfDATA::MenuCars_t::PrepareData ()
{
    for (auto& pic : buttons)
        pic.set_scale (1.6f , 1.6f);

    int texts_num = 0;
    for (auto& text : texts)
    {
        if (texts_num == 4 || texts_num == 5)
            text.set_color (sf::Color::Black);
        else
            text.set_color (sf::Color::Magenta);
        texts_num++;
    }

    for (auto& level : levels)
        level.set_color (sf::Color::Blue);

    sf::FloatRect car_pic1 = car1.get_loc_bounds ();
    sf::FloatRect car_pic2 = car2.get_loc_bounds ();
    car1.set_origin (car_pic1.width / 2.f , car_pic1.height / 2.f);
    car2.set_origin (car_pic2.width / 2.f , car_pic2.height / 2.f);
}
//**************************************

//!data::main_game
//--------------------------------------
std::array<sfC::Text_t , 4> sfDATA::MainGame_t::texts = {
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 35, sf::Vector2f (sfCON::WindowWidth * 0.508f, 30.f), "First car "),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 35, sf::Vector2f (sfCON::WindowWidth * 0.540f, 65.f), "0"),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 35, sf::Vector2f (sfCON::WindowWidth * 0.39f, 30.f), "Second car "),
    sfC::Text_t ("../Fonts/nfs-mw3.ttf", 35, sf::Vector2f (sfCON::WindowWidth * 0.422f, 65.f), "0"),
};

sf::View sfDATA::MainGame_t::view1 (sf::FloatRect (0 , 0 , sfCON::WindowWidth * 0.48f , sfCON::WindowHeight));
sf::View sfDATA::MainGame_t::view2 (sf::FloatRect (0 , 0 , sfCON::WindowWidth * 0.48f , sfCON::WindowHeight));
sf::View sfDATA::MainGame_t::full_view (sf::FloatRect (0 , 0 , sfCON::WindowWidth , sfCON::WindowHeight));

sfC::Picture_t sfDATA::MainGame_t::mid_strip ("../Images/strip.png" , sf::IntRect (743 , 0 , sfCON::WindowWidth / 100 , sfCON::WindowHeight) , sf::Vector2f (sfCON::WindowWidth * 0.495f , 0.f));
sfC::Map sfDATA::MainGame_t::map ("../Images/blocks3.png");

sfC::Car_t sfDATA::MainGame_t::tank1 (&sfDATA::MainGame_t::map , "../Images/cars.png" , sf::IntRect (93 , 268 , 44 , 78) , sf::Vector2f (80.f , 80.f) , sf::Color (255 , 255 , 255) , 0.7f);
sfC::Car_t sfDATA::MainGame_t::tank2 (&sfDATA::MainGame_t::map , "../Images/cars.png" , sf::IntRect (93 , 138 , 44 , 78) , sf::Vector2f (80.f , 80.f) , sf::Color (255 , 255 , 255) , 0.7f);

bool sfDATA::MainGame_t::AnalyseGame (sf::RenderWindow& window , float time)
{
    if (CheckWin ())
        return false;

    sf::Event event;
    sfC::Direction_t moving_tank1;
    sfC::Direction_t moving_tank2;

    while (window.pollEvent (event))
    {
        if (event.type == sf::Event::Closed)
            return false;

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            sfDATA::MenuCars_t::MenuCars (window);
            return false;
        }

        moving_tank1.CheckKeyboard (event.type , event.key.code , sfC::Direction_t::Type::Arrows);
        moving_tank2.CheckKeyboard (event.type , event.key.code , sfC::Direction_t::Type::WASD);
    }

    tank1.move_car (moving_tank1 , time);//NEED TANK1
    tank2.move_car (moving_tank2 , time);//NEED TANK2

    return true;
}

bool sfDATA::MainGame_t::MainGame (sf::RenderWindow& window , const sfC::ParamCar_t& sort1 , const sfC::ParamCar_t& sort2)
{
    //SO MANY NEEDS
    tank1.set_sort (sort1);//NEED TANK
    tank2.set_sort (sort2);//NEED TANK

    sf::Clock clock;
    float time = 0;

    while (window.isOpen ())
    {
        time = static_cast<float>(clock.getElapsedTime ().asMicroseconds () / 800.0);
        clock.restart ();

        if (!sfDATA::MainGame_t::AnalyseGame (window , time))
        {
            window.close ();
            return false;
        }

        window.clear ();

        //first player
        window.setView (view1);
        window.draw (map);
        window.draw (tank1.for_draw ());
        window.draw (tank2.for_draw ());

        //second player
        window.setView (view2);
        window.draw (map);
        window.draw (tank1.for_draw ());
        window.draw (tank2.for_draw ());

        //middle strip
        window.setView (full_view);
        window.draw (mid_strip.for_draw ());

        for (const auto& text : texts)
            window.draw (text.for_draw ());

        window.display ();
    }

    return true;
}

bool sfDATA::MainGame_t::CheckWin ()
{
    //map, tank1, tank2, tests[1], textx[3]
    if (map.is_finish (std::move (tank1.get_boundaries ())))
    {

        if (!sfF::change_text_num (texts[1] , 1))
            ERROR ("Can't change text!");

        tank1.restart ();
        tank2.restart ();
    }

    if (map.is_finish (std::move (tank2.get_boundaries ())))
    {

        if (!sfF::change_text_num (texts[3] , 1))
            ERROR ("Can't change text!");
        tank1.restart ();
        tank2.restart ();
    }
    return false;
}

bool sfDATA::MainGame_t::read_map (const std::string& name , sfC::Map& cur_map /* = data::main_game::map*/)
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

void sfDATA::MainGame_t::Restart ()
{
    sfF::RestartCar (tank1);
    sfF::RestartCar (tank2);

    texts[1].set_text ("0");
    texts[3].set_text ("0");
}

void sfDATA::MainGame_t::PrepareData (sfC::Map& create_map)
{
    sfDATA::MainGame_t::read_map ("Begin" , sfDATA::MainGame_t::map);
    sfDATA::MainGame_t::read_map ("Begin" , create_map);

    for (auto& text : sfDATA::MainGame_t::texts)
        text.set_color (sf::Color::Blue);

    sfDATA::MainGame_t::tank1.rotate (180.f);
    sfDATA::MainGame_t::tank2.rotate (180.f);

    sfDATA::MainGame_t::view1.setViewport (sf::FloatRect (0.505f , 0.f , 0.495f , 1.f));
    sfDATA::MainGame_t::view2.setViewport (sf::FloatRect (0.f , 0.f , 0.495f , 1.f));

    sfDATA::MainGame_t::tank1.set_view (&sfDATA::MainGame_t::view1);
    sfDATA::MainGame_t::tank2.set_view (&sfDATA::MainGame_t::view2);
}
//--------------------------------------

// !data::create_map
//++++++++++++++++++++++++++++++++++++++

//sfDATA::MainMenu
////////////////////////////////////////
sfC::Picture_t sfDATA::MainMenu_t::main_pic_ ("../Images/menu.png" , sf::IntRect (0 , 0 , sfCON::WindowWidth , sfCON::WindowHeight) , sf::Vector2f (0 , 0));

sf::IntRect sfDATA::MainMenu_t::released_ (301 , 377 , 199 , 64);
sf::IntRect sfDATA::MainMenu_t::pressed_ (570 , 377 , 199 , 64);
int sfDATA::MainMenu_t::cur_press_ = 0;

std::array<sfC::Picture_t , sfDATA::MainMenu_t::count_buttons_> sfDATA::MainMenu_t::buttons_ = {
    sfC::Picture_t ("../Images/buttons2.png", sfDATA::MainMenu_t::pressed_, sf::Vector2f (sfCON::WindowWidth / 3, sfCON::WindowHeight / 10), sf::Color (255, 255, 255), sf::Vector2f (1.2f, 1.2f)),
    sfC::Picture_t ("../Images/buttons2.png", sfDATA::MainMenu_t::released_, sf::Vector2f (sfCON::WindowWidth / 3, sfCON::WindowHeight / 10 + 170), sf::Color (255, 255, 255), sf::Vector2f (1.2f, 1.2f)),
    sfC::Picture_t ("../Images/buttons2.png", sfDATA::MainMenu_t::released_, sf::Vector2f (sfCON::WindowWidth / 3, sfCON::WindowHeight / 10 + 340), sf::Color (255, 255, 255), sf::Vector2f (1.2f, 1.2f)),
    sfC::Picture_t ("../Images/buttons2.png", sfDATA::MainMenu_t::released_, sf::Vector2f (sfCON::WindowWidth / 3, sfCON::WindowHeight / 10 + 510), sf::Color (255, 255, 255), sf::Vector2f (1.2f, 1.2f)),
    sfC::Picture_t ("../Images/buttons2.png", sfDATA::MainMenu_t::released_, sf::Vector2f (sfCON::WindowWidth / 3, sfCON::WindowHeight / 10 + 680), sf::Color (255, 255, 255), sf::Vector2f (1.2f, 1.2f)) };

std::array<sfC::Text_t , sfDATA::MainMenu_t::count_buttons_> sfDATA::MainMenu_t::texts_ = {
    sfC::Text_t ("../Fonts/baltimore-nouveau.ttf", 40, sf::Vector2f (sfCON::WindowWidth / 3 + 49, sfCON::WindowHeight / 10 + 13), "PLAY"),
    sfC::Text_t ("../Fonts/baltimore-nouveau.ttf", 22, sf::Vector2f (sfCON::WindowWidth / 3 + 46, sfCON::WindowHeight / 10 + 196), "Restart"),
    sfC::Text_t ("../Fonts/baltimore-nouveau.ttf", 22, sf::Vector2f (sfCON::WindowWidth / 3 + 23, sfCON::WindowHeight / 10 + 368), "Downaload"),
    sfC::Text_t ("../Fonts/baltimore-nouveau.ttf", 22, sf::Vector2f (sfCON::WindowWidth / 3 + 56, sfCON::WindowHeight / 10 + 536), "Create"),
    sfC::Text_t ("../Fonts/baltimore-nouveau.ttf", 22, sf::Vector2f (sfCON::WindowWidth / 3 + 83, sfCON::WindowHeight / 10 + 707), "Exit") };
////////////////////////////////////////

bool sfDATA::MainMenu_t::AnalyseMenu (sf::RenderWindow& window)
{
    //CHANGE STATIC
    //  sfDATA::MainMenu_t::buttons
    //  sfDATA::MainMenu_t::cur_press

    sf::Event event;
    while (window.pollEvent (event))
    {

        if (event.type == sf::Event::Closed)
            return false;

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                return false;

            case sf::Keyboard::Enter:
                if (!ActionPress (window , cur_press_))
                    return false;
                break;

            case sf::Keyboard::Up:
                if (cur_press_ > 0)
                {
                    buttons_[cur_press_].set_texture (released_);
                    cur_press_--;
                    buttons_[cur_press_].set_texture (pressed_);
                }
                break;

            case sf::Keyboard::Down:
                if (cur_press_ < count_buttons_ - 1)
                {
                    buttons_[cur_press_].set_texture (released_);
                    cur_press_++;
                    buttons_[cur_press_].set_texture (pressed_);
                }
                break;

            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f cur_coord (static_cast<float>(event.mouseMove.x) , static_cast<float>(event.mouseMove.y));

            for (int i = 0; i < count_buttons_; ++i)
            {
                if (buttons_[i].get_glob_bounds ().contains (cur_coord))
                {
                    buttons_[cur_press_].set_texture (released_);
                    cur_press_ = i;
                    buttons_[cur_press_].set_texture (pressed_);
                    break;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left &&
                buttons_[cur_press_].get_glob_bounds ().contains (static_cast<float>(event.mouseButton.x) , static_cast<float>(event.mouseButton.y)))
            {
                if (!ActionPress (window , cur_press_))
                    return false;
            }
        }
    }

    return true;
}

bool sfDATA::MainMenu_t::ActionPress (sf::RenderWindow& window , int press)
{
    switch (press)
    {
    case type_button_::GAME:
        MenuCars_t::MenuCars (window);
        return false;

    case type_button_::RESTART:
        Full_Restart ();
        Text_t::ShowDoneAction (window , "Restarted");
        return true;

    case type_button_::SET:
        Text_t::SetMap (window);
        return true;

    case type_button_::CREATE:
        CreateMap_t::CreateMap (window);
        return true;

    case type_button_::EXIT:
        return false;

    default:
        WARNING ("Existing not done action!\n");
    }
    return false;
}

bool sfDATA::MainMenu_t::MainMenu (sf::RenderWindow& window)
{
    sf::View main_view (sf::FloatRect (0.f , 0.f , sfCON::WindowWidth , sfCON::WindowHeight));
    while (window.isOpen ())
    {
        if (!AnalyseMenu (window))
            return false;

        window.clear ();
        window.draw (main_pic_.for_draw ());

        for (const auto& button : buttons_)
            window.draw (button.for_draw ());

        for (const auto& text : texts_)
            window.draw (text.for_draw ());

        window.setView (main_view);
        window.display ();
    }

    return false;
}

void sfDATA::MainMenu_t::PrepareData ()
{
    for (auto& text : texts_)
        text.set_color (sf::Color::Blue);
}