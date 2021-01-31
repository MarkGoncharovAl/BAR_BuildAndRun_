#include "ALL.hpp"
#include "../Common_libs/Errors/Errors.hpp"

namespace sfDATA
{
    void Full_Restart()
    {
        MenuCars_t::Restart();
        MainGame_t::Restart();
    }

    void PrepareData()
    {
        MainMenu_t::PrepareData();
        CreateMap_t::PrepareData();
        MenuCars_t::PrepareData();
        MapPrototypes_t::PrepareData();
        Text_t::PrepareData();
    }
} // namespace sfDATA

bool AnalyseGame(sf::RenderWindow &window, float time)
{
    using cur_data = sfDATA::MainGame_t;

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
            sfDATA::MenuCars_t::MenuCars(window);
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
    using cur_data = sfDATA::MainGame_t;

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
    using cur_data = sfDATA::MainGame_t;

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
    using cur_data = sfDATA::Text_t;
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

//data::menu_cars
//**************************************
sfC::Picture_t sfDATA::MenuCars_t::main_pic("../Images/menu3.png", sf::IntRect(0, 0, sfCON::WindowWidth, sfCON::WindowHeight), sf::Vector2f(0, 0));

std::string sfDATA::MenuCars_t::file_buttons("../Images/buttons2.png");
sf::IntRect sfDATA::MenuCars_t::tex_rect(32, 498, 198, 64);

std::array<sfC::Picture_t, 4> sfDATA::MenuCars_t::main_buttons = {
    sfC::Picture_t(sfDATA::MenuCars_t::file_buttons, sf::IntRect(32, 377, 198, 64), sf::Vector2f(sfCON::WindowWidth / 2.2f - 15.f, sfCON::WindowHeight / 10.f), sf::Color(sf::Color::White)),
    sfC::Picture_t(sfDATA::MenuCars_t::file_buttons, sf::IntRect(32, 377, 198, 64), sf::Vector2f(sfCON::WindowWidth / 2.2f - 15.f, sfCON::WindowHeight / 6.f), sf::Color(sf::Color::White)),
    sfC::Picture_t("../Images/direction.png", sf::IntRect(40, 133, 1231, 1037), sf::Vector2f(30.f, 620.f), sf::Color(sf::Color::White), sf::Vector2f(0.05f, 0.05f)),
    sfC::Picture_t("../Images/direction.png", sf::IntRect(1271, 133, -1231, 1037), sf::Vector2f(1793.f, 620.f), sf::Color(sf::Color::White), sf::Vector2f(0.05f, 0.05f)),
};

std::array<sfC::Picture_t, 8> sfDATA::MenuCars_t::buttons = {
    sfC::Picture_t(sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f(sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f), sf::Color(255, 255, 255)),
    sfC::Picture_t(sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f(sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f + 100), sf::Color(255, 255, 255)),
    sfC::Picture_t(sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f(sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f + 200), sf::Color(255, 255, 255)),
    sfC::Picture_t(sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f(sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f + 300), sf::Color(255, 255, 255)),
    sfC::Picture_t(sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f(sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f), sf::Color(255, 255, 255)),
    sfC::Picture_t(sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f(sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f + 100), sf::Color(255, 255, 255)),
    sfC::Picture_t(sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f(sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f + 200), sf::Color(255, 255, 255)),
    sfC::Picture_t(sfDATA::MenuCars_t::file_buttons, sfDATA::MenuCars_t::tex_rect, sf::Vector2f(sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f + 300), sf::Color(255, 255, 255)),
};
std::array<sfC::Text_t, 6> sfDATA::MenuCars_t::texts = {
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f(sfCON::WindowWidth / 3 + 100, sfCON::WindowHeight / 1.8f + 10), "Acceleration"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f(sfCON::WindowWidth / 3 + 150, sfCON::WindowHeight / 1.8f + 110), "Max speed"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f(sfCON::WindowWidth / 3 + 80, sfCON::WindowHeight / 1.8f + 210), "Rotate speed"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f(sfCON::WindowWidth / 3 + 170, sfCON::WindowHeight / 1.8f + 310), "Controll"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 45, sf::Vector2f(sfCON::WindowWidth / 2.1f - 25.f, sfCON::WindowHeight / 9.7f), "PLAY"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 45, sf::Vector2f(sfCON::WindowWidth / 2.1f - 25.f, sfCON::WindowHeight / 5.8f), "EXIT")};

std::array<sfC::Text_t, 8> sfDATA::MenuCars_t::levels = {
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 10), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 110), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 210), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 310), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 10), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 110), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 210), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 310), "0")};

sfC::Picture_t sfDATA::MenuCars_t::car1("../Images/cars.png", sf::IntRect(93, 268, 44, 78), sf::Vector2f(1640.f, 150.f), sf::Color(255, 255, 255), sf::Vector2f(2.f, 2.f));
sfC::Picture_t sfDATA::MenuCars_t::car2("../Images/cars.png", sf::IntRect(93, 138, 44, 78), sf::Vector2f(260.f, 150.f), sf::Color(255, 255, 255), sf::Vector2f(2.f, 2.f));
sfC::MenuCars_t sfDATA::MenuCars_t::data;

sfC::ParamCar_t sfDATA::MenuCars_t::sort1 = sfCON::sort_tank_BASE;
sfC::ParamCar_t sfDATA::MenuCars_t::sort2 = sfCON::sort_tank_BASE;

void sfDATA::MenuCars_t::Restart()
{
    data.restart();
    main_buttons[2].set_position(30.f, 620.f);
    main_buttons[3].set_position(1793.f, 620.f);

    sort1 = sfCON::sort_tank_BASE;
    sort2 = sfCON::sort_tank_BASE;

    for (auto &text : levels)
        text.set_text("0");
}

bool sfDATA::MenuCars_t::AnalyseMenuCars(sf::RenderWindow &window)
{
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
                    sfDATA::MainMenu_t::MainMenu(window);
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
                sfDATA::MainMenu_t::MainMenu(window);
                return false;
            default:
                break;
            }
        }
    }

    return true;
}

bool sfDATA::MenuCars_t::MenuCars(sf::RenderWindow &window)
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

void sfDATA::MenuCars_t::PrepareData()
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

    sf::FloatRect car_pic1 = car1.get_loc_bounds();
    sf::FloatRect car_pic2 = car2.get_loc_bounds();
    car1.set_origin(car_pic1.width / 2.f, car_pic1.height / 2.f);
    car2.set_origin(car_pic2.width / 2.f, car_pic2.height / 2.f);
}
//**************************************

//!data::main_game
//--------------------------------------
std::array<sfC::Text_t, 4> sfDATA::MainGame_t::texts = {
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 35, sf::Vector2f(sfCON::WindowWidth * 0.508f, 30.f), "First car "),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 35, sf::Vector2f(sfCON::WindowWidth * 0.540f, 65.f), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 35, sf::Vector2f(sfCON::WindowWidth * 0.39f, 30.f), "Second car "),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 35, sf::Vector2f(sfCON::WindowWidth * 0.422f, 65.f), "0"),
};

sf::View sfDATA::MainGame_t::view1(sf::FloatRect(0, 0, sfCON::WindowWidth * 0.48f, sfCON::WindowHeight));
sf::View sfDATA::MainGame_t::view2(sf::FloatRect(0, 0, sfCON::WindowWidth * 0.48f, sfCON::WindowHeight));
sf::View sfDATA::MainGame_t::full_view(sf::FloatRect(0, 0, sfCON::WindowWidth, sfCON::WindowHeight));

sfC::Picture_t sfDATA::MainGame_t::mid_strip("../Images/strip.png", sf::IntRect(743, 0, sfCON::WindowWidth / 100, sfCON::WindowHeight), sf::Vector2f(sfCON::WindowWidth * 0.495f, 0.f));
sfC::Map sfDATA::MainGame_t::map("../Images/blocks3.png");

sfC::Car_t sfDATA::MainGame_t::tank1(&sfDATA::MainGame_t::map, "../Images/cars.png", sf::IntRect(93, 268, 44, 78), sf::Vector2f(80.f, 80.f), sf::Color(255, 255, 255), 0.7f);
sfC::Car_t sfDATA::MainGame_t::tank2(&sfDATA::MainGame_t::map, "../Images/cars.png", sf::IntRect(93, 138, 44, 78), sf::Vector2f(80.f, 80.f), sf::Color(255, 255, 255), 0.7f);

bool sfDATA::MainGame_t::read_map(const std::string &name, sfC::Map &cur_map /* = data::main_game::map*/)
{
    if (name.empty())
        return false;

    std::ifstream file("../MapTiles/" + name + ".txt", std::ios::in);
    if (!file.is_open())
        return false;

    sf::Vector2i count_blocks, total_size, block_size;
    file >> count_blocks.x >> count_blocks.y >> total_size.x >> total_size.y >> block_size.x >> block_size.y;

    Matrix_t<int> arr(count_blocks.x, count_blocks.y);
    file >> arr;

    cur_map.create_map(sfC::MapPrototype(count_blocks, block_size, arr));
    return true;
}

void sfDATA::MainGame_t::Restart()
{
    sfF::RestartCar(tank1);
    sfF::RestartCar(tank2);

    texts[1].set_text("0");
    texts[3].set_text("0");
}

void sfDATA::MainGame_t::PrepareData(sfC::Map &create_map)
{
    sfDATA::MainGame_t::read_map("Begin", sfDATA::MainGame_t::map);
    sfDATA::MainGame_t::read_map("Begin", create_map);

    for (auto &text : sfDATA::MainGame_t::texts)
        text.set_color(sf::Color::Blue);

    sfDATA::MainGame_t::tank1.rotate(180.f);
    sfDATA::MainGame_t::tank2.rotate(180.f);

    sfDATA::MainGame_t::view1.setViewport(sf::FloatRect(0.505f, 0.f, 0.495f, 1.f));
    sfDATA::MainGame_t::view2.setViewport(sf::FloatRect(0.f, 0.f, 0.495f, 1.f));

    sfDATA::MainGame_t::tank1.set_view(&sfDATA::MainGame_t::view1);
    sfDATA::MainGame_t::tank2.set_view(&sfDATA::MainGame_t::view2);
}
//--------------------------------------

// !data::create_map
//++++++++++++++++++++++++++++++++++++++
sfC::Map sfDATA::CreateMap_t::map("../Images/blocks3.png");
sfC::Picture_t sfDATA::CreateMap_t::info_user("../Images/To_create_menu.png", sf::IntRect(243, 277, 180, 265), sf::Vector2f(10.f, 812.f), sf::Color::Magenta);

sf::View sfDATA::CreateMap_t::view(sf::FloatRect(0.f, 0.f, sfCON::WindowWidth, sfCON::WindowHeight));

std::map<sfDATA::CreateMap_t::data_for_keys, bool> sfDATA::CreateMap_t::keys;

std::stack<sfDATA::CreateMap_t::data_for_stack> sfDATA::CreateMap_t::actions;

sfC::BlockPrototype::TypeBlock sfDATA::CreateMap_t::cur_block = sfC::BlockPrototype::TypeBlock::Wall;

void sfDATA::CreateMap_t::update_mouse(int x, int y) noexcept
{
    if (x < sfCON::WindowWidth * 0.1f)
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Left] = true;
    else
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Left] = false;
    if (x > sfCON::WindowWidth * 0.85f)
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Right] = true;
    else
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Right] = false;
    if (y < sfCON::WindowHeight * 0.15f)
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Up] = true;
    else
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Up] = false;
    if (y > sfCON::WindowHeight * 0.80f)
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Down] = true;
    else
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Down] = false;
}
void sfDATA::CreateMap_t::update_block(const sf::Vector2i &block, sfC::BlockPrototype::TypeBlock type) noexcept
{
    sfC::BlockPrototype::TypeBlock old_type = sfDATA::CreateMap_t::map.get_type_block(block);

    if (sfDATA::CreateMap_t::map.change_block(block, type))
    {

        if (sfDATA::CreateMap_t::actions.empty())
        {
            sfDATA::CreateMap_t::actions.push(sfDATA::CreateMap_t::data_for_stack(block, old_type));
            return;
        }
        if (!sfDATA::CreateMap_t::actions.top().is_equal(block, type))
            sfDATA::CreateMap_t::actions.push(sfDATA::CreateMap_t::data_for_stack(block, old_type));
    }
}
void sfDATA::CreateMap_t::cancel_last_update() noexcept
{
    if (!sfDATA::CreateMap_t::actions.empty())
    {
        sfDATA::CreateMap_t::data_for_stack prev_block = sfDATA::CreateMap_t::actions.top();
        sfDATA::CreateMap_t::actions.pop();

        sfDATA::CreateMap_t::map.change_block(prev_block.block, prev_block.type);
    }
}
void sfDATA::CreateMap_t::move_view() noexcept
{
    sfDATA::CreateMap_t::view.move(
        sfCON::SPEED_CAMERA * sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Right] - sfCON::SPEED_CAMERA * sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Left],
        sfCON::SPEED_CAMERA * sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Down] - sfCON::SPEED_CAMERA * sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Up]);
}
void sfDATA::CreateMap_t::clear_stack() noexcept
{
    while (!sfDATA::CreateMap_t::actions.empty())
        sfDATA::CreateMap_t::actions.pop();
}

void sfDATA::CreateMap_t::PrepareData()
{
    MainGame_t::PrepareData(sfDATA::CreateMap_t::map);

    sfDATA::CreateMap_t::keys.insert(std::make_pair(sfDATA::CreateMap_t::data_for_keys::Button_Left, false));
    sfDATA::CreateMap_t::keys.insert(std::make_pair(sfDATA::CreateMap_t::data_for_keys::Ctrl, false));
    sfDATA::CreateMap_t::keys.insert(std::make_pair(sfDATA::CreateMap_t::data_for_keys::Z, false));
    sfDATA::CreateMap_t::keys.insert(std::make_pair(sfDATA::CreateMap_t::data_for_keys::Mouse_Down, false));
    sfDATA::CreateMap_t::keys.insert(std::make_pair(sfDATA::CreateMap_t::data_for_keys::Mouse_Up, false));
    sfDATA::CreateMap_t::keys.insert(std::make_pair(sfDATA::CreateMap_t::data_for_keys::Mouse_Right, false));
    sfDATA::CreateMap_t::keys.insert(std::make_pair(sfDATA::CreateMap_t::data_for_keys::Mouse_Left, false));
}
//++++++++++++++++++++++++++++++++++++++

// !data::map_prototypes
//======================================
std::vector<std::string> sfDATA::MapPrototypes_t::maps;
constexpr char sfDATA::MapPrototypes_t::main_file[];

bool sfDATA::MapPrototypes_t::insert_map(const std::string &name, const sfC::MapPrototype &map)
{
    std::vector<std::string>::iterator cur_iter = std::find(maps.begin(), maps.end(), name);

    if (cur_iter != maps.end())
    {
        write_map_into_file("../MapTiles/" + name + ".txt", map);
        return true;
    }
    else if (maps.size() <= max_size)
    {
        maps.push_back(name);
        write_name_new_map(name);
        write_map_into_file("../MapTiles/" + name + ".txt", map);
        return true;
    }

    return false;
}

void sfDATA::MapPrototypes_t::write_map_into_file(const std::string &file, const sfC::MapPrototype &map)
{
    std::ofstream out(file, std::ios::out);

    map.dump_interrior(out);
    if (!out.good())
        ERROR("File wasn't writen down properly!");

    out.close();
}

void sfDATA::MapPrototypes_t::write_name_new_map(const std::string &file)
{
    std::fstream cur_file(sfDATA::MapPrototypes_t::main_file, std::ios::app);
    cur_file << file << std::endl;
    cur_file.close();
}

void sfDATA::MapPrototypes_t::PrepareData()
{
    std::ifstream cur_file(sfDATA::MapPrototypes_t::main_file, std::ios::in);
    if (!cur_file.is_open())
        ERROR(std::string("Can't open the main file ") + sfDATA::MapPrototypes_t::main_file);

    while (!cur_file.eof())
    {
        std::string cur_str;
        cur_file >> cur_str;
        if (cur_str.empty())
            break;

        sfDATA::MapPrototypes_t::maps.push_back(cur_str);
    }

    cur_file.close();

    SetMap_t::PrepareData(maps);
}
//======================================

//  data::text
//((((((((((((((((((((((((((((((((((((((
sfC::Picture_t sfDATA::Text_t::background("../Images/Saving2.png", sf::IntRect(0, 0, sfCON::WindowWidth, sfCON::WindowHeight), sf::Vector2f(0.f, 0.f), sf::Color::Magenta);

sfC::Text_t sfDATA::Text_t::main_text("../Fonts/nfs-mw3.ttf", 120, sf::Vector2f(sfCON::WindowWidth * 0.1f, sfCON::WindowHeight * 0.35f), "Create map");
sfC::Text_t sfDATA::Text_t::addition_text("../Fonts/19413.ttf", 100, sf::Vector2f(sfCON::WindowWidth * 0.1f, sfCON::WindowHeight * 0.5f), "NAME: ");

sf::View sfDATA::Text_t::view(sf::FloatRect(0.f, 0.f, sfCON::WindowWidth, sfCON::WindowHeight));

sfC::Text_t sfDATA::Text_t::show_down_action1("../Fonts/19413.ttf", 120, sf::Vector2f(sfCON::WindowWidth * 0.05f, sfCON::WindowHeight * 0.44f));
sfC::Text_t sfDATA::Text_t::show_down_action2("../Fonts/19413.ttf", 80, sf::Vector2f(sfCON::WindowWidth * 0.05f, sfCON::WindowHeight * 0.6f));

void sfDATA::Text_t::PrepareData()
{
    main_text.set_color(sf::Color::Red);
    addition_text.set_color(sf::Color::Red);
    show_down_action1.set_color(sf::Color::Red);
    show_down_action2.set_color(sf::Color::Red);
}
//((((((((((((((((((((((((((((((((((((((
//  data::set_map
//))))))))))))))))))))))))))))))))))))))
sfC::Text_t sfDATA::SetMap_t::main_text("../Fonts/nfs-mw3.ttf", 100, sf::Vector2f(sfCON::WindowWidth * 0.1f, sfCON::WindowHeight * 0.25f), "Download map");

size_t sfDATA::SetMap_t::cur_map = 0;
sfC::Text_t sfDATA::SetMap_t::cur_text("../Fonts/19413.ttf", 200, sf::Vector2f(sfCON::WindowWidth * 0.1f, sfCON::WindowHeight * 0.5f), "");
sfC::Picture_t sfDATA::SetMap_t::direct_back("../Images/direct.png", sf::IntRect(109, 22, -87, 59), sf::Vector2f(0.f, 0.f), sf::Color::White);

void sfDATA::SetMap_t::PrepareData(std::vector<std::string> &maps)
{
    cur_text.set_text(maps.at(cur_map));
    main_text.set_color(sf::Color::Red);
    cur_text.set_color(sf::Color::Red);
}
//((((((((((((((((((((((((((((((((((((((

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
std::string sfDATA::Text_t::WaitTextUser(sf::RenderWindow &window)
{
    std::string text;
    sfC::Text_t user_text("../Fonts/19413.ttf", 100, sf::Vector2f(sfCON::WindowWidth * 0.3f, sfCON::WindowHeight * 0.5f), "");
    user_text.set_color(sf::Color::Cyan);

    window.setView(view);

    while (window.isOpen())
    {
        if (!AnalyseWait_Text_User(window, text, user_text))
            break;

        window.clear(sf::Color::White);
        window.draw(background.for_draw());
        window.draw(main_text.for_draw());
        window.draw(addition_text.for_draw());
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
                if (!sfDATA::MainGame_t::read_map(sfDATA::SetMap_t::cur_text.get_text()))
                {
                    ShowDoneAction(window, "Not selected!");
                    return true;
                }
                else
                {
                    ShowDoneAction(window, sfDATA::SetMap_t::cur_text.get_text(), "selected");
                    return false;
                }
                break;
            case sf::Keyboard::Right:
                if (sfDATA::SetMap_t::cur_map + 1 < sfDATA::MapPrototypes_t::maps.size())
                {
                    sfDATA::SetMap_t::cur_map += 1;
                    sfDATA::SetMap_t::cur_text.set_text(sfDATA::MapPrototypes_t::maps.at(sfDATA::SetMap_t::cur_map));
                }
                break;
            case sf::Keyboard::Left:
                if (sfDATA::SetMap_t::cur_map > 0)
                {
                    sfDATA::SetMap_t::cur_map--;
                    sfDATA::SetMap_t::cur_text.set_text(sfDATA::MapPrototypes_t::maps.at(sfDATA::SetMap_t::cur_map));
                }
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left &&
                sfDATA::SetMap_t::direct_back.is_include(event.mouseButton.x, event.mouseButton.y))
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
    using cur_data = sfDATA::Text_t;

    window.setView(cur_data::view);

    while (window.isOpen())
    {

        if (!AnalyseSetMap(window))
        {
            break;
        }

        window.clear();
        window.draw(cur_data::background.for_draw());
        window.draw(sfDATA::SetMap_t::main_text.for_draw());
        window.draw(sfDATA::SetMap_t::cur_text.for_draw());
        window.draw(sfDATA::SetMap_t::direct_back.for_draw());
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
                ShowDoneAction(window, sfDATA::SetMap_t::cur_text.get_text(), "selected");
                return false;
                break;
            case sf::Keyboard::Right:
                if (sfDATA::SetMap_t::cur_map + 1 < sfDATA::MapPrototypes_t::maps.size())
                {
                    sfDATA::SetMap_t::cur_map += 1;
                    sfDATA::SetMap_t::cur_text.set_text(sfDATA::MapPrototypes_t::maps.at(sfDATA::SetMap_t::cur_map));
                }
                break;
            case sf::Keyboard::Left:
                if (sfDATA::SetMap_t::cur_map > 0)
                {
                    sfDATA::SetMap_t::cur_map--;
                    sfDATA::SetMap_t::cur_text.set_text(sfDATA::MapPrototypes_t::maps.at(sfDATA::SetMap_t::cur_map));
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
    using cur_data = sfDATA::Text_t;

    window.setView(cur_data::view);

    while (window.isOpen())
    {

        if (!AnalysePrepareCreateMap(window))
        {
            break;
        }

        window.clear();
        window.draw(cur_data::background.for_draw());
        window.draw(sfDATA::SetMap_t::main_text.for_draw());
        window.draw(sfDATA::SetMap_t::cur_text.for_draw());
        window.display();
    }

    sfDATA::MainGame_t::read_map(sfDATA::SetMap_t::cur_text.get_text(), map);
}

bool AnalyseCreateMap(sf::RenderWindow &window)
{
    using cur_data = sfDATA::CreateMap_t;

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
                    std::string new_name = sfDATA::Text_t::WaitTextUser(window);

                    if (!new_name.empty())
                    {
                        ShowDoneAction(window, new_name, "created");
                        sfDATA::MapPrototypes_t::insert_map(new_name, cur_data::map.get_map_prototype());
                    }
                    else
                    {
                        ShowDoneAction(window, "Not created!");
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
    using cur_data = sfDATA::CreateMap_t;
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

//sfDATA::MainMenu
////////////////////////////////////////
sfC::Picture_t sfDATA::MainMenu_t::main_pic_("../Images/menu.png", sf::IntRect(0, 0, sfCON::WindowWidth, sfCON::WindowHeight), sf::Vector2f(0, 0));

sf::IntRect sfDATA::MainMenu_t::released_(301, 377, 199, 64);
sf::IntRect sfDATA::MainMenu_t::pressed_(570, 377, 199, 64);
int sfDATA::MainMenu_t::cur_press_ = 0;

std::array<sfC::Picture_t, sfDATA::MainMenu_t::count_buttons_> sfDATA::MainMenu_t::buttons_ = {
    sfC::Picture_t("../Images/buttons2.png", sfDATA::MainMenu_t::pressed_, sf::Vector2f(sfCON::WindowWidth / 3, sfCON::WindowHeight / 10), sf::Color(255, 255, 255), sf::Vector2f(1.2f, 1.2f)),
    sfC::Picture_t("../Images/buttons2.png", sfDATA::MainMenu_t::released_, sf::Vector2f(sfCON::WindowWidth / 3, sfCON::WindowHeight / 10 + 170), sf::Color(255, 255, 255), sf::Vector2f(1.2f, 1.2f)),
    sfC::Picture_t("../Images/buttons2.png", sfDATA::MainMenu_t::released_, sf::Vector2f(sfCON::WindowWidth / 3, sfCON::WindowHeight / 10 + 340), sf::Color(255, 255, 255), sf::Vector2f(1.2f, 1.2f)),
    sfC::Picture_t("../Images/buttons2.png", sfDATA::MainMenu_t::released_, sf::Vector2f(sfCON::WindowWidth / 3, sfCON::WindowHeight / 10 + 510), sf::Color(255, 255, 255), sf::Vector2f(1.2f, 1.2f)),
    sfC::Picture_t("../Images/buttons2.png", sfDATA::MainMenu_t::released_, sf::Vector2f(sfCON::WindowWidth / 3, sfCON::WindowHeight / 10 + 680), sf::Color(255, 255, 255), sf::Vector2f(1.2f, 1.2f))};

std::array<sfC::Text_t, sfDATA::MainMenu_t::count_buttons_> sfDATA::MainMenu_t::texts_ = {
    sfC::Text_t("../Fonts/baltimore-nouveau.ttf", 40, sf::Vector2f(sfCON::WindowWidth / 3 + 49, sfCON::WindowHeight / 10 + 13), "PLAY"),
    sfC::Text_t("../Fonts/baltimore-nouveau.ttf", 22, sf::Vector2f(sfCON::WindowWidth / 3 + 46, sfCON::WindowHeight / 10 + 196), "Restart"),
    sfC::Text_t("../Fonts/baltimore-nouveau.ttf", 22, sf::Vector2f(sfCON::WindowWidth / 3 + 23, sfCON::WindowHeight / 10 + 368), "Downaload"),
    sfC::Text_t("../Fonts/baltimore-nouveau.ttf", 22, sf::Vector2f(sfCON::WindowWidth / 3 + 56, sfCON::WindowHeight / 10 + 536), "Create"),
    sfC::Text_t("../Fonts/baltimore-nouveau.ttf", 22, sf::Vector2f(sfCON::WindowWidth / 3 + 83, sfCON::WindowHeight / 10 + 707), "Exit")};
////////////////////////////////////////

bool sfDATA::MainMenu_t::AnalyseMenu(sf::RenderWindow &window)
{
    //CHANGE STATIC
    //  sfDATA::MainMenu_t::buttons
    //  sfDATA::MainMenu_t::cur_press

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
                if (!ActionPress(window, cur_press_))
                    return false;
                break;

            case sf::Keyboard::Up:
                if (cur_press_ > 0)
                {
                    buttons_[cur_press_].set_texture(released_);
                    cur_press_--;
                    buttons_[cur_press_].set_texture(pressed_);
                }
                break;

            case sf::Keyboard::Down:
                if (cur_press_ < count_buttons_ - 1)
                {
                    buttons_[cur_press_].set_texture(released_);
                    cur_press_++;
                    buttons_[cur_press_].set_texture(pressed_);
                }
                break;

            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f cur_coord(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));

            for (int i = 0; i < count_buttons_; ++i)
            {
                if (buttons_[i].get_glob_bounds().contains(cur_coord))
                {
                    buttons_[cur_press_].set_texture(released_);
                    cur_press_ = i;
                    buttons_[cur_press_].set_texture(pressed_);
                    break;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left &&
                buttons_[cur_press_].get_glob_bounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
            {
                if (!ActionPress(window, cur_press_))
                    return false;
            }
        }
    }

    return true;
}

bool sfDATA::MainMenu_t::ActionPress(sf::RenderWindow &window, int press)
{
    switch (press)
    {
    case type_button_::GAME:
        MenuCars_t::MenuCars(window);
        return false;

    case type_button_::RESTART:
        Full_Restart();
        ShowDoneAction(window, "Restarted");
        return true;

    case type_button_::SET:
        SetMap(window);
        return true;

    case type_button_::CREATE:
        CreateMap(window);
        return true;

    case type_button_::EXIT:
        return false;

    default:
        WARNING("Existing not done action!\n");
    }
    return false;
}

bool sfDATA::MainMenu_t::MainMenu(sf::RenderWindow &window)
{
    sf::View main_view(sf::FloatRect(0.f, 0.f, sfCON::WindowWidth, sfCON::WindowHeight));
    while (window.isOpen())
    {
        if (!AnalyseMenu(window))
            return false;

        window.clear();
        window.draw(main_pic_.for_draw());

        for (const auto &button : buttons_)
            window.draw(button.for_draw());

        for (const auto &text : texts_)
            window.draw(text.for_draw());

        window.setView(main_view);
        window.display();
    }

    return false;
}

void sfDATA::MainMenu_t::PrepareData()
{
    for (auto &text : texts_)
        text.set_color(sf::Color::Blue);
}