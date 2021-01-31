#include "Menus.hpp"
#include "../Common_libs/Errors/Errors.hpp"

//!Should be replaced
#include "Main/MenusMain.hpp"

namespace sfDATA
{
    //!Constants
    sfC::Picture_t MenuCars::main_pic("../Images/menu3.png", sf::IntRect(0, 0, sfCON::WindowWidth, sfCON::WindowHeight), sf::Vector2f(0, 0));

    std::string MenuCars::file_buttons("../Images/buttons2.png");
    sf::IntRect MenuCars::tex_rect(32, 498, 198, 64);

    std::array<sfC::Picture_t, 4> MenuCars::main_buttons = {
        sfC::Picture_t(MenuCars::file_buttons, sf::IntRect(32, 377, 198, 64), sf::Vector2f(sfCON::WindowWidth / 2.2f - 15.f, sfCON::WindowHeight / 10.f), sf::Color(sf::Color::White)),
        sfC::Picture_t(MenuCars::file_buttons, sf::IntRect(32, 377, 198, 64), sf::Vector2f(sfCON::WindowWidth / 2.2f - 15.f, sfCON::WindowHeight / 6.f), sf::Color(sf::Color::White)),
        sfC::Picture_t("../Images/direction.png", sf::IntRect(40, 133, 1231, 1037), sf::Vector2f(30.f, 620.f), sf::Color(sf::Color::White), sf::Vector2f(0.05f, 0.05f)),
        sfC::Picture_t("../Images/direction.png", sf::IntRect(1271, 133, -1231, 1037), sf::Vector2f(1793.f, 620.f), sf::Color(sf::Color::White), sf::Vector2f(0.05f, 0.05f)),
    };

    std::array<sfC::Picture_t, 8> MenuCars::buttons = {
        sfC::Picture_t(MenuCars::file_buttons, MenuCars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f), sf::Color(255, 255, 255)),
        sfC::Picture_t(MenuCars::file_buttons, MenuCars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f + 100), sf::Color(255, 255, 255)),
        sfC::Picture_t(MenuCars::file_buttons, MenuCars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f + 200), sf::Color(255, 255, 255)),
        sfC::Picture_t(MenuCars::file_buttons, MenuCars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f + 300), sf::Color(255, 255, 255)),
        sfC::Picture_t(MenuCars::file_buttons, MenuCars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f), sf::Color(255, 255, 255)),
        sfC::Picture_t(MenuCars::file_buttons, MenuCars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f + 100), sf::Color(255, 255, 255)),
        sfC::Picture_t(MenuCars::file_buttons, MenuCars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f + 200), sf::Color(255, 255, 255)),
        sfC::Picture_t(MenuCars::file_buttons, MenuCars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f + 300), sf::Color(255, 255, 255)),
    };
    std::array<sfC::Text_t, 6> MenuCars::texts = {
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f(sfCON::WindowWidth / 3 + 100, sfCON::WindowHeight / 1.8f + 10), "Acceleration"),
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f(sfCON::WindowWidth / 3 + 150, sfCON::WindowHeight / 1.8f + 110), "Max speed"),
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f(sfCON::WindowWidth / 3 + 80, sfCON::WindowHeight / 1.8f + 210), "Rotate speed"),
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f(sfCON::WindowWidth / 3 + 170, sfCON::WindowHeight / 1.8f + 310), "Controll"),
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 45, sf::Vector2f(sfCON::WindowWidth / 2.1f - 25.f, sfCON::WindowHeight / 9.7f), "PLAY"),
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 45, sf::Vector2f(sfCON::WindowWidth / 2.1f - 25.f, sfCON::WindowHeight / 5.8f), "EXIT")};

    std::array<sfC::Text_t, 8> MenuCars::levels = {
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 10), "0"),
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 110), "0"),
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 210), "0"),
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 310), "0"),
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 10), "0"),
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 110), "0"),
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 210), "0"),
        sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 310), "0")};

    sfC::Picture_t MenuCars::car1("../Images/cars.png", sf::IntRect(93, 268, 44, 78), sf::Vector2f(1640.f, 150.f), sf::Color(255, 255, 255), sf::Vector2f(2.f, 2.f));
    sfC::Picture_t MenuCars::car2("../Images/cars.png", sf::IntRect(93, 138, 44, 78), sf::Vector2f(260.f, 150.f), sf::Color(255, 255, 255), sf::Vector2f(2.f, 2.f));
    sfC::MenuCars_t MenuCars::data;

    sfC::ParamCar_t MenuCars::sort1 = sfCON::sort_tank_BASE;
    sfC::ParamCar_t MenuCars::sort2 = sfCON::sort_tank_BASE;

} // namespace sfDATA

namespace sfDATA
{

    bool MenuCars::AnalyseMenuCars(sf::RenderWindow &window)
    {
        // CHANGE STATIC
        //  data::MenuCars::data
        //  data::MenuCars::main_buttons
        //  data::MenuCars::levels
        //  data::MenuCars::sort1 (and sort2 too)

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    if (main_buttons[0].get_glob_bounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
                    {
                        MainGame(window, sort1, sort2);
                        return false;
                    }
                    if (main_buttons[1].get_glob_bounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
                    {
                        sfDATA::MainMenu::ChechMainMenu(window);
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
                        main_buttons[2].move(0.f, 100.f);
                    }
                    break;
                case sf::Keyboard::W:
                    if (data.pos_left != 0)
                    {
                        data.pos_left--;
                        main_buttons[2].move(0.f, -100.f);
                    }
                    break;
                case sf::Keyboard::D:
                    if (data.lvl_left[data.pos_left] != sfCON::levels_char)
                    {
                        data.lvl_left[data.pos_left]++;
                        change_data_cars(sort2, data.pos_left, sfC::ParamCar_t::Do::Increase);

                        if (!sfF::change_text_num(levels[data.pos_left], 1))
                            ERROR("Can't change num");
                    }
                    break;
                case sf::Keyboard::A:
                    if (data.lvl_left[data.pos_left] != 0)
                    {
                        data.lvl_left[data.pos_left]--;
                        change_data_cars(sort2, data.pos_left, sfC::ParamCar_t::Do::Decrease);

                        if (!sfF::change_text_num(levels[data.pos_left], -1))
                            ERROR("Can't change num");
                    }
                    break;
                case sf::Keyboard::Down:
                    if (data.pos_right != 3)
                    {
                        data.pos_right++;
                        main_buttons[3].move(0.f, 100.f);
                    }
                    break;
                case sf::Keyboard::Up:
                    if (data.pos_right != 0)
                    {
                        data.pos_right--;
                        main_buttons[3].move(0.f, -100.f);
                    }
                    break;
                case sf::Keyboard::Right:
                    if (data.lvl_right[data.pos_right] != sfCON::levels_char)
                    {
                        data.lvl_right[data.pos_right]++;
                        change_data_cars(sort1, data.pos_right, sfC::ParamCar_t::Do::Increase);

                        if (!sfF::change_text_num(levels[4 + data.pos_right], 1))
                            ERROR("Can't change num");
                    }
                    break;
                case sf::Keyboard::Left:
                    if (data.lvl_right[data.pos_right] != 0)
                    {
                        data.lvl_right[data.pos_right]--;
                        change_data_cars(sort1, data.pos_right, sfC::ParamCar_t::Do::Decrease);

                        if (!sfF::change_text_num(levels[4 + data.pos_right], -1))
                            ERROR("Can't change num");
                    }
                    break;
                case sf::Keyboard::Enter:
                    MainGame(window, sort1, sort2);
                    return false;
                case sf::Keyboard::Escape:
                    sfDATA::MainMenu::ChechMainMenu(window);
                    return false;
                default:
                    break;
                }
            }
        }

        return true;
    }

    bool MenuCars::CheckMenuCars(sf::RenderWindow &window)
    {

        while (window.isOpen())
        {

            if (!AnalyseMenuCars(window))
                break;

            window.clear();
            window.draw(main_pic.for_draw());

            window.draw(car1.for_draw());
            window.draw(car2.for_draw());
            car1.rotate(0.2f);
            car2.rotate(0.2f);

            for (const auto &button : main_buttons)
                window.draw(button.for_draw());

            for (const auto &pic : buttons)
                window.draw(pic.for_draw());

            for (const auto &text : texts)
                window.draw(text.for_draw());

            for (const auto &level : levels)
                window.draw(level.for_draw());

            window.display();
        }

        return false;
    }

    void MenuCars::prepare_data_MenuCars()
    {
        for (auto &pic : buttons)
            pic.set_scale(1.6f, 1.6f);

        int texts_num = 0;
        for (auto &text : texts)
        {
            if (texts_num == 4 || texts_num == 5)
                text.set_color(sf::Color::Black);
            else
                text.set_color(sf::Color::Magenta);
            texts_num++;
        }

        for (auto &level : levels)
            level.set_color(sf::Color::Blue);

        sf::FloatRect pic_car1 = car1.get_loc_bounds();
        sf::FloatRect pic_car2 = car2.get_loc_bounds();
        car1.set_origin(pic_car1.width / 2.f, pic_car1.height / 2.f);
        car2.set_origin(pic_car2.width / 2.f, pic_car2.height / 2.f);
    }

    void MenuCars::Restart()
    {
        data.restart();
        main_buttons[2].set_position(30.f, 620.f);
        main_buttons[3].set_position(1793.f, 620.f);

        sort1 = sfCON::sort_tank_BASE;
        sort2 = sfCON::sort_tank_BASE;

        for (auto &text : levels)
            text.set_text("0");
    }

} // namespace sfDATA

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
    sfC::Text_t user_text("../Fonts/19413.ttf", 100, sf::Vector2f(sfCON::WindowWidth * 0.3f, sfCON::WindowHeight * 0.5f), "");
    user_text.set_color(sf::Color::Cyan);

    window.setView(cur_data::view);

    while (window.isOpen())
    {

        if (!AnalyseWait_Text_User(window, text, user_text))
            break;

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
                sfDATA::ShowDoneAction(window, "Not selected");
                return false;
                break;
            case sf::Keyboard::Enter:
                if (!data::main_game::read_map(data::set_map::cur_text.get_text()))
                {
                    sfDATA::ShowDoneAction(window, "Not selected!");
                    return true;
                }
                else
                {
                    sfDATA::ShowDoneAction(window, data::set_map::cur_text.get_text(), "selected");
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

                sfDATA::ShowDoneAction(window, "Not selected");
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
                sfDATA::ShowDoneAction(window, data::set_map::cur_text.get_text(), "selected");
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
void PrepareCreateMap(sf::RenderWindow &window, sfC::Map &map)
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

                if ((coords.x > sfCON::SIZE_BLOCK && coords.x < cur_data::map.GetSize().x - sfCON::SIZE_BLOCK) &&
                    (coords.y > sfCON::SIZE_BLOCK && coords.y < cur_data::map.GetSize().y - sfCON::SIZE_BLOCK))
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

                if ((coords.x > sfCON::SIZE_BLOCK && coords.x < cur_data::map.GetSize().x - sfCON::SIZE_BLOCK) &&
                    (coords.y > sfCON::SIZE_BLOCK && coords.y < cur_data::map.GetSize().y - sfCON::SIZE_BLOCK))
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
                        sfDATA::ShowDoneAction(window, new_name, "created");
                        data::map_prototypes::insert_map(new_name, cur_data::map.get_map_prototype());
                    }
                    else
                    {
                        sfDATA::ShowDoneAction(window, "Not created!");
                    }
                }
                break;
            case sf::Keyboard::Num1:
                cur_data::cur_block = sfC::BlockPrototype::TypeBlock::Field;
                break;
            case sf::Keyboard::Num2:
                cur_data::cur_block = sfC::BlockPrototype::TypeBlock::Wall;
                break;
            case sf::Keyboard::Num3:
                cur_data::cur_block = sfC::BlockPrototype::TypeBlock::Target;
                break;
            case sf::Keyboard::Num4:
                cur_data::cur_block = sfC::BlockPrototype::TypeBlock::Sand;
                break;
            case sf::Keyboard::Num5:
                cur_data::cur_block = sfC::BlockPrototype::TypeBlock::Acceleration;
                break;
            case sf::Keyboard::Num6:
                cur_data::cur_block = sfC::BlockPrototype::TypeBlock::Restart;
                break;
            case sf::Keyboard::Escape:
                sfDATA::ShowDoneAction(window, "Not created");
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