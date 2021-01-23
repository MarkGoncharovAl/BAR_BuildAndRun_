#include "Menus.h"

bool AnalyseMenu(sf::RenderWindow &window)
{
    //CHANGE STATIC
    //  data::main_menu::buttons
    //  data::main_menu::cur_press
    using cur_data = data::main_menu;

    sf::Event event;
    while (window.pollEvent(event))
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
                switch (cur_data::cur_press)
                {
                case 0:
                    MenuCars(window);
                    return false;
                    break;
                case 1:
                    Full_Restart();
                    ShowDoneAction(window, "Restarted");
                    break;

                case 2:
                    SetMap(window);
                    break;
                case 3:
                    CreateMap(window);
                    break;
                case 4:
                    return false;
                    break;
                }
                break;

            case sf::Keyboard::Up:
                if (cur_data::cur_press > 0)
                {
                    cur_data::buttons[cur_data::cur_press].set_texture(cur_data::released);
                    cur_data::cur_press--;
                    cur_data::buttons[cur_data::cur_press].set_texture(cur_data::pressed);
                }
                break;
            case sf::Keyboard::Down:
                if (cur_data::cur_press < 4)
                {
                    cur_data::buttons[cur_data::cur_press].set_texture(cur_data::released);
                    cur_data::cur_press++;
                    cur_data::buttons[cur_data::cur_press].set_texture(cur_data::pressed);
                }
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f cur_coord(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));

            for (int i = 0; i < 5; ++i)
            {
                if (cur_data::buttons[i].get_glob_bounds().contains(cur_coord))
                {
                    cur_data::buttons[cur_data::cur_press].set_texture(cur_data::released);
                    cur_data::cur_press = i;
                    cur_data::buttons[cur_data::cur_press].set_texture(cur_data::pressed);
                    break;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left &&
                cur_data::buttons[cur_data::cur_press].get_glob_bounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
            {

                switch (cur_data::cur_press)
                {
                case 0:
                    MenuCars(window);
                    return false;
                    break;
                case 1:
                    Full_Restart();
                    ShowDoneAction(window, "Restarted");
                    break;
                case 2:
                    SetMap(window);
                    break;
                case 3:
                    CreateMap(window);
                    break;
                case 4:
                    return false;
                    break;
                }
            }
        }
    }

    return true;
}
bool MainMenu(sf::RenderWindow &window)
{
    using cur_data = data::main_menu;

    sf::View main_view(sf::FloatRect(0.f, 0.f, CON::WindowWidth, CON::WindowHeight));
    while (window.isOpen())
    {

        if (!AnalyseMenu(window))
        {
            return false;
        }

        window.clear();
        window.draw(data::main_menu::main_pic.for_draw());

        for (const auto &button : cur_data::buttons)
            window.draw(button.for_draw());

        for (const auto &text : cur_data::texts)
            window.draw(text.for_draw());

        window.setView(main_view);
        window.display();
    }
    return false;
}

bool AnalyseMenuCars(sf::RenderWindow &window)
{
    // CHANGE STATIC
    //  data::menu_cars::data
    //  data::menu_cars::main_buttons
    //  data::menu_cars::levels
    //  data::menu_cars::sort1 (and sort2 too)

    using cur_data = data::menu_cars;

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {

                if (cur_data::main_buttons[0].get_glob_bounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
                {
                    MainGame(window, cur_data::sort1, cur_data::sort2);
                    return false;
                }
                if (cur_data::main_buttons[1].get_glob_bounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
                {
                    MainMenu(window);
                    return false;
                }
            }
        }
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::S:
                if (cur_data::data.pos_left != 3)
                {
                    cur_data::data.pos_left++;
                    cur_data::main_buttons[2].move(0.f, 100.f);
                }
                break;
            case sf::Keyboard::W:
                if (cur_data::data.pos_left != 0)
                {
                    cur_data::data.pos_left--;
                    cur_data::main_buttons[2].move(0.f, -100.f);
                }
                break;
            case sf::Keyboard::D:
                if (cur_data::data.lvl_left[cur_data::data.pos_left] != CON::levels_char)
                {
                    cur_data::data.lvl_left[cur_data::data.pos_left]++;
                    change_data_cars(cur_data::sort2, cur_data::data.pos_left, sfC::ParamCar_t::Do::Increase);

                    if (!sfF::change_text_num(cur_data::levels[cur_data::data.pos_left], 1))
                        ERROR("Can't change num");
                }
                break;
            case sf::Keyboard::A:
                if (cur_data::data.lvl_left[cur_data::data.pos_left] != 0)
                {
                    cur_data::data.lvl_left[cur_data::data.pos_left]--;
                    change_data_cars(cur_data::sort2, cur_data::data.pos_left, sfC::ParamCar_t::Do::Decrease);

                    if (!sfF::change_text_num(cur_data::levels[cur_data::data.pos_left], -1))
                        ERROR("Can't change num");
                }
                break;
            case sf::Keyboard::Down:
                if (cur_data::data.pos_right != 3)
                {
                    cur_data::data.pos_right++;
                    cur_data::main_buttons[3].move(0.f, 100.f);
                }
                break;
            case sf::Keyboard::Up:
                if (cur_data::data.pos_right != 0)
                {
                    cur_data::data.pos_right--;
                    cur_data::main_buttons[3].move(0.f, -100.f);
                }
                break;
            case sf::Keyboard::Right:
                if (cur_data::data.lvl_right[cur_data::data.pos_right] != CON::levels_char)
                {
                    cur_data::data.lvl_right[cur_data::data.pos_right]++;
                    change_data_cars(cur_data::sort1, cur_data::data.pos_right, sfC::ParamCar_t::Do::Increase);

                    if (!sfF::change_text_num(cur_data::levels[4 + cur_data::data.pos_right], 1))
                        ERROR("Can't change num");
                }
                break;
            case sf::Keyboard::Left:
                if (cur_data::data.lvl_right[cur_data::data.pos_right] != 0)
                {
                    cur_data::data.lvl_right[cur_data::data.pos_right]--;
                    change_data_cars(cur_data::sort1, cur_data::data.pos_right, sfC::ParamCar_t::Do::Decrease);

                    if (!sfF::change_text_num(cur_data::levels[4 + cur_data::data.pos_right], -1))
                        ERROR("Can't change num");
                }
                break;
            case sf::Keyboard::Enter:
                MainGame(window, cur_data::sort1, cur_data::sort2);
                return false;
            case sf::Keyboard::Escape:
                MainMenu(window);
                return false;
            default:
                break;
            }
        }
    }

    return true;
}
bool MenuCars(sf::RenderWindow &window)
{

    using cur_data = data::menu_cars;

    while (window.isOpen())
    {

        if (!AnalyseMenuCars(window))
        {
            break;
        }

        window.clear();
        window.draw(data::menu_cars::main_pic.for_draw());

        window.draw(cur_data::car1.for_draw());
        window.draw(cur_data::car2.for_draw());
        cur_data::car1.rotate(0.2f);
        cur_data::car2.rotate(0.2f);

        for (const auto &button : cur_data::main_buttons)
            window.draw(button.for_draw());

        for (const auto &pic : cur_data::buttons)
            window.draw(pic.for_draw());

        for (const auto &text : cur_data::texts)
            window.draw(text.for_draw());

        for (const auto &level : cur_data::levels)
            window.draw(level.for_draw());

        window.display();
    }

    return false;
}

bool AnalyseWait_Text_User(sf::RenderWindow &window, std::string &text, sfC::Text_t &user_text)
{
    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::KeyPressed)
        {

            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                text.clear();
                return false;
                break;
            case sf::Keyboard::Enter:
                return false;
                break;
            case sf::Keyboard::BackSpace:
            case sf::Keyboard::Delete:
                text.pop_back();
                user_text.pop_back();
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::TextEntered)
        {

            if (sfF::IS_ASKII(event.text.unicode))
            {

                char cur_symbol = static_cast<char>(event.text.unicode);
                text.push_back(cur_symbol);
                user_text.push_back(cur_symbol);
            }
        }
    }
    return true;
}
std::string Wait_Text_User(sf::RenderWindow &window)
{
    using cur_data = data::text;

    std::string text;
    sfC::Text_t user_text("Fonts/19413.ttf", 100, sf::Vector2f(CON::WindowWidth * 0.3f, CON::WindowHeight * 0.5f), "");
    user_text.set_color(sf::Color::Cyan);

    window.setView(cur_data::view);

    while (window.isOpen())
    {

        if (!AnalyseWait_Text_User(window, text, user_text))
        {
            break;
        }

        window.clear(sf::Color::White);
        window.draw(cur_data::background.for_draw());
        window.draw(cur_data::main_text.for_draw());
        window.draw(cur_data::addition_text.for_draw());
        window.draw(user_text.for_draw());
        window.display();
    }

    return text;
}

bool AnalyseSetMap(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::KeyPressed)
        {

            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                ShowDoneAction(window, "Not selected");
                return false;
                break;
            case sf::Keyboard::Enter:
                if (!data::main_game::read_map(data::set_map::cur_text.get_text()))
                {
                    ShowDoneAction(window, "Not selected!");
                    return true;
                }
                else
                {
                    ShowDoneAction(window, data::set_map::cur_text.get_text(), "selected");
                    return false;
                }
                break;
            case sf::Keyboard::Right:
                if (data::set_map::cur_map + 1 < data::map_prototypes::maps.size())
                {
                    data::set_map::cur_map += 1;
                    data::set_map::cur_text.set_text(data::map_prototypes::maps.at(data::set_map::cur_map));
                }
                break;
            case sf::Keyboard::Left:
                if (data::set_map::cur_map > 0)
                {
                    data::set_map::cur_map--;
                    data::set_map::cur_text.set_text(data::map_prototypes::maps.at(data::set_map::cur_map));
                }
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left &&
                data::set_map::direct_back.is_include(event.mouseButton.x, event.mouseButton.y))
            {

                ShowDoneAction(window, "Not selected");
                return false;
            }
        }
    }
    return true;
}
bool SetMap(sf::RenderWindow &window)
{
    using cur_data = data::text;

    window.setView(cur_data::view);

    while (window.isOpen())
    {

        if (!AnalyseSetMap(window))
        {
            break;
        }

        window.clear();
        window.draw(cur_data::background.for_draw());
        window.draw(data::set_map::main_text.for_draw());
        window.draw(data::set_map::cur_text.for_draw());
        window.draw(data::set_map::direct_back.for_draw());
        window.display();
    }

    return false;
}

bool AnalysePrepareCreateMap(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::KeyPressed)
        {

            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
                ShowDoneAction(window, data::set_map::cur_text.get_text(), "selected");
                return false;
                break;
            case sf::Keyboard::Right:
                if (data::set_map::cur_map + 1 < data::map_prototypes::maps.size())
                {
                    data::set_map::cur_map += 1;
                    data::set_map::cur_text.set_text(data::map_prototypes::maps.at(data::set_map::cur_map));
                }
                break;
            case sf::Keyboard::Left:
                if (data::set_map::cur_map > 0)
                {
                    data::set_map::cur_map--;
                    data::set_map::cur_text.set_text(data::map_prototypes::maps.at(data::set_map::cur_map));
                }
                break;
            default:
                break;
            }
        }
    }
    return true;
}
void PrepareCreateMap(sf::RenderWindow &window, M::Map &map)
{
    using cur_data = data::text;

    window.setView(cur_data::view);

    while (window.isOpen())
    {

        if (!AnalysePrepareCreateMap(window))
        {
            break;
        }

        window.clear();
        window.draw(cur_data::background.for_draw());
        window.draw(data::set_map::main_text.for_draw());
        window.draw(data::set_map::cur_text.for_draw());
        window.display();
    }

    data::main_game::read_map(data::set_map::cur_text.get_text(), map);
}

bool AnalyseCreateMap(sf::RenderWindow &window)
{
    using cur_data = data::create_map;

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            return false;
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {

                sf::Vector2f coords(event.mouseButton.x + sfF::get_view_position_x(cur_data::view),
                                    event.mouseButton.y + sfF::get_view_position_y(cur_data::view));

                if ((coords.x > CON::SIZE_BLOCK && coords.x < cur_data::map.get_size_x() - CON::SIZE_BLOCK) &&
                    (coords.y > CON::SIZE_BLOCK && coords.y < cur_data::map.get_size_y() - CON::SIZE_BLOCK))
                {
                    cur_data::update_block(
                        cur_data::map.AbsCoords(coords), cur_data::cur_block);
                }

                cur_data::keys[cur_data::data_for_keys::Button_Left] = true;
            }
        }
        if (event.type == sf::Event::MouseMoved)
        {
            if (cur_data::keys[cur_data::data_for_keys::Button_Left])
            {

                sf::Vector2f coords(event.mouseMove.x + sfF::get_view_position_x(cur_data::view),
                                    event.mouseMove.y + sfF::get_view_position_y(cur_data::view));

                if ((coords.x > CON::SIZE_BLOCK && coords.x < cur_data::map.get_size_x() - CON::SIZE_BLOCK) &&
                    (coords.y > CON::SIZE_BLOCK && coords.y < cur_data::map.get_size_y() - CON::SIZE_BLOCK))
                {
                    cur_data::update_block(
                        cur_data::map.AbsCoords(coords), cur_data::cur_block);
                }
            }

            cur_data::update_mouse(event.mouseMove.x, event.mouseMove.y);
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
                cur_data::keys[cur_data::data_for_keys::Button_Left] = false;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::LControl:
                cur_data::keys[cur_data::data_for_keys::Ctrl] = true;
                break;
            case sf::Keyboard::Z:
                cur_data::keys[cur_data::data_for_keys::Z] = true;
                if (cur_data::keys[cur_data::data_for_keys::Ctrl] == true)
                    cur_data::cancel_last_update();
                break;
            case sf::Keyboard::S:
                cur_data::keys[cur_data::data_for_keys::S] = true;
                if (cur_data::keys[cur_data::data_for_keys::Ctrl] == true)
                {
                    std::string new_name = Wait_Text_User(window);

                    if (!new_name.empty())
                    {
                        ShowDoneAction(window, new_name, "created");
                        data::map_prototypes::insert_map(new_name, cur_data::map.get_map_prototype());
                    }
                    else
                    {
                        ShowDoneAction(window, "Not created!");
                    }
                }
                break;
            case sf::Keyboard::Num1:
                cur_data::cur_block = M::BLOCKS::Field;
                break;
            case sf::Keyboard::Num2:
                cur_data::cur_block = M::BLOCKS::Wall;
                break;
            case sf::Keyboard::Num3:
                cur_data::cur_block = M::BLOCKS::Target;
                break;
            case sf::Keyboard::Num4:
                cur_data::cur_block = M::BLOCKS::Sand;
                break;
            case sf::Keyboard::Num5:
                cur_data::cur_block = M::BLOCKS::Acceleration;
                break;
            case sf::Keyboard::Num6:
                cur_data::cur_block = M::BLOCKS::Restart;
                break;
            case sf::Keyboard::Escape:
                ShowDoneAction(window, "Not created");
                return false;
                break;
            default:
                break;
            }
        }
        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::LControl:
                cur_data::keys[cur_data::data_for_keys::Ctrl] = false;
                break;
            case sf::Keyboard::Z:
                cur_data::keys[cur_data::data_for_keys::Z] = false;
                break;
            case sf::Keyboard::S:
                cur_data::keys[cur_data::data_for_keys::S] = false;
                break;
            default:
                break;
            }
        }
    }

    cur_data::move_view();
    return true;
}
bool CreateMap(sf::RenderWindow &window)
{
    using cur_data = data::create_map;
    PrepareCreateMap(window, cur_data::map);

    while (window.isOpen())
    {

        if (!AnalyseCreateMap(window))
            break;

        window.clear();

        window.setView(cur_data::view);
        window.draw(cur_data::map);

        cur_data::info_user.set_position(
            sfF::get_view_position_x(cur_data::view),
            765.f + sfF::get_view_position_y(cur_data::view));
        window.draw(cur_data::info_user.for_draw());
        window.display();
    }

    return false;
}