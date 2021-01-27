#include "Actions.hpp"
#include "../Help/Direction/Direction.hpp"

void Full_Restart()
{
    data::menu_cars::data.restart();
    data::menu_cars::main_buttons[2].set_position(30.f, 620.f);
    data::menu_cars::main_buttons[3].set_position(1793.f, 620.f);

    data::menu_cars::sort1 = sfCON::sort_tank_BASE;
    data::menu_cars::sort2 = sfCON::sort_tank_BASE;

    for (auto &text : data::menu_cars::levels)
        text.set_text("0");

    sfF::RestartCar(data::main_game::tank1);
    sfF::RestartCar(data::main_game::tank2);

    data::main_game::texts[1].set_text("0");
    data::main_game::texts[3].set_text("0");
}

bool AnalyseGame(sf::RenderWindow &window, float time)
{
    using cur_data = data::main_game;

    if (CheckWin())
        return false;

    sf::Event event;
    sfC::Direction_t moving_tank1;
    sfC::Direction_t moving_tank2;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            return false;

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            MenuCars(window);
            return false;
        }

        moving_tank1.CheckKeyboard(event.type, event.key.code, sfC::Direction_t::Type::Arrows);
        moving_tank2.CheckKeyboard(event.type, event.key.code, sfC::Direction_t::Type::WASD);
    }

    cur_data::tank1.move_car(moving_tank1, time);
    cur_data::tank2.move_car(moving_tank2, time);

    return true;
}
bool MainGame(sf::RenderWindow &window, const sfC::ParamCar_t &sort1, const sfC::ParamCar_t &sort2)
{
    using cur_data = data::main_game;

    cur_data::tank1.set_sort(sort1);
    cur_data::tank2.set_sort(sort2);

    sf::Clock clock;
    float time = 0;

    while (window.isOpen())
    {
        time = static_cast<float>(clock.getElapsedTime().asMicroseconds() / 800.0);
        clock.restart();

        if (!AnalyseGame(window, time))
        {
            window.close();
            return false;
        }

        window.clear();

        //first player
        window.setView(cur_data::view1);
        window.draw(cur_data::map);
        window.draw(cur_data::tank1.for_draw());
        window.draw(cur_data::tank2.for_draw());

        //second player
        window.setView(cur_data::view2);
        window.draw(cur_data::map);
        window.draw(cur_data::tank1.for_draw());
        window.draw(cur_data::tank2.for_draw());

        //middle strip
        window.setView(cur_data::full_view);
        window.draw(cur_data::mid_strip.for_draw());

        for (const auto &text : cur_data::texts)
            window.draw(text.for_draw());

        window.display();
    }

    return true;
}

bool CheckWin()
{
    using cur_data = data::main_game;

    if (cur_data::map.is_finish(std::move(cur_data::tank1.get_boundaries())))
    {

        if (!sfF::change_text_num(cur_data::texts[1], 1))
            ERROR("Can't change text!");

        cur_data::tank1.restart();
        cur_data::tank2.restart();
    }
    if (cur_data::map.is_finish(std::move(cur_data::tank2.get_boundaries())))
    {

        if (!sfF::change_text_num(cur_data::texts[3], 1))
            ERROR("Can't change text!");
        cur_data::tank1.restart();
        cur_data::tank2.restart();
    }
    return false;
}

// !CHANGE IT - FIND FUNCTIONS
void change_data_cars(sfC::ParamCar_t &sort, int proper, sfC::ParamCar_t::Do action /* = sfC::ParamCar_t::Do::Increase*/)
{
    sort.CorrectProperties(proper, action);
}

void ShowDoneAction(sf::RenderWindow &window, const std::string &info1, const std::string &info2 /* = std::string()*/)
{
    using cur_data = data::text;
    constexpr int64_t max_time = 1000000;

    cur_data::show_down_action1.set_text(info1);
    cur_data::show_down_action2.set_text(info2);
    sf::Clock clock;
    clock.restart();

    if (info2.empty())
    {
        while (window.isOpen() && clock.getElapsedTime().asMicroseconds() < max_time)
        {

            window.clear();

            window.draw(cur_data::background.for_draw());
            window.draw(cur_data::show_down_action1.for_draw());

            window.display();
        }
    }
    else
    {
        while (window.isOpen() && clock.getElapsedTime().asMicroseconds() < max_time)
        {

            window.clear();

            window.draw(cur_data::background.for_draw());
            window.draw(cur_data::show_down_action1.for_draw());
            window.draw(cur_data::show_down_action2.for_draw());

            window.display();
        }
    }
}