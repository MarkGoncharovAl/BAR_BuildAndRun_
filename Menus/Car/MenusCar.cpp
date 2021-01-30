#include "MenusCar.hpp"
#include "../../Help/Help.hpp"
#include "../Main/MenusMain.hpp"
#include "../../Actions/Actions.hpp"

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

        using cur_data = MenuCars;

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