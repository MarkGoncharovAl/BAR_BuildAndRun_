#include "Data.hpp"

//!Should be deleted
#include "../../Menus/Main/MenusMain.hpp"

//data::menu_cars
//**************************************
sfC::Picture_t data::menu_cars::main_pic("../Images/menu3.png", sf::IntRect(0, 0, sfCON::WindowWidth, sfCON::WindowHeight), sf::Vector2f(0, 0));

std::string data::menu_cars::file_buttons("../Images/buttons2.png");
sf::IntRect data::menu_cars::tex_rect(32, 498, 198, 64);

std::array<sfC::Picture_t, 4> data::menu_cars::main_buttons = {
    sfC::Picture_t(data::menu_cars::file_buttons, sf::IntRect(32, 377, 198, 64), sf::Vector2f(sfCON::WindowWidth / 2.2f - 15.f, sfCON::WindowHeight / 10.f), sf::Color(sf::Color::White)),
    sfC::Picture_t(data::menu_cars::file_buttons, sf::IntRect(32, 377, 198, 64), sf::Vector2f(sfCON::WindowWidth / 2.2f - 15.f, sfCON::WindowHeight / 6.f), sf::Color(sf::Color::White)),
    sfC::Picture_t("../Images/direction.png", sf::IntRect(40, 133, 1231, 1037), sf::Vector2f(30.f, 620.f), sf::Color(sf::Color::White), sf::Vector2f(0.05f, 0.05f)),
    sfC::Picture_t("../Images/direction.png", sf::IntRect(1271, 133, -1231, 1037), sf::Vector2f(1793.f, 620.f), sf::Color(sf::Color::White), sf::Vector2f(0.05f, 0.05f)),
};

std::array<sfC::Picture_t, 8> data::menu_cars::buttons = {
    sfC::Picture_t(data::menu_cars::file_buttons, data::menu_cars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f), sf::Color(255, 255, 255)),
    sfC::Picture_t(data::menu_cars::file_buttons, data::menu_cars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f + 100), sf::Color(255, 255, 255)),
    sfC::Picture_t(data::menu_cars::file_buttons, data::menu_cars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f + 200), sf::Color(255, 255, 255)),
    sfC::Picture_t(data::menu_cars::file_buttons, data::menu_cars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 20, sfCON::WindowHeight / 1.8f + 300), sf::Color(255, 255, 255)),
    sfC::Picture_t(data::menu_cars::file_buttons, data::menu_cars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f), sf::Color(255, 255, 255)),
    sfC::Picture_t(data::menu_cars::file_buttons, data::menu_cars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f + 100), sf::Color(255, 255, 255)),
    sfC::Picture_t(data::menu_cars::file_buttons, data::menu_cars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f + 200), sf::Color(255, 255, 255)),
    sfC::Picture_t(data::menu_cars::file_buttons, data::menu_cars::tex_rect, sf::Vector2f(sfCON::WindowWidth / 1.3f, sfCON::WindowHeight / 1.8f + 300), sf::Color(255, 255, 255)),
};
std::array<sfC::Text_t, 6> data::menu_cars::texts = {
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f(sfCON::WindowWidth / 3 + 100, sfCON::WindowHeight / 1.8f + 10), "Acceleration"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f(sfCON::WindowWidth / 3 + 150, sfCON::WindowHeight / 1.8f + 110), "Max speed"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f(sfCON::WindowWidth / 3 + 80, sfCON::WindowHeight / 1.8f + 210), "Rotate speed"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 70, sf::Vector2f(sfCON::WindowWidth / 3 + 170, sfCON::WindowHeight / 1.8f + 310), "Controll"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 45, sf::Vector2f(sfCON::WindowWidth / 2.1f - 25.f, sfCON::WindowHeight / 9.7f), "PLAY"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 45, sf::Vector2f(sfCON::WindowWidth / 2.1f - 25.f, sfCON::WindowHeight / 5.8f), "EXIT")};

std::array<sfC::Text_t, 8> data::menu_cars::levels = {
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 10), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 110), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 210), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 20 + 140, sfCON::WindowHeight / 1.8f + 310), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 10), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 110), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 210), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 60, sf::Vector2f(sfCON::WindowWidth / 1.3f + 140, sfCON::WindowHeight / 1.8f + 310), "0")};

sfC::Picture_t data::menu_cars::car1("../Images/cars.png", sf::IntRect(93, 268, 44, 78), sf::Vector2f(1640.f, 150.f), sf::Color(255, 255, 255), sf::Vector2f(2.f, 2.f));
sfC::Picture_t data::menu_cars::car2("../Images/cars.png", sf::IntRect(93, 138, 44, 78), sf::Vector2f(260.f, 150.f), sf::Color(255, 255, 255), sf::Vector2f(2.f, 2.f));
sfC::MenuCars_t data::menu_cars::data;

sfC::ParamCar_t data::menu_cars::sort1 = sfCON::sort_tank_BASE;
sfC::ParamCar_t data::menu_cars::sort2 = sfCON::sort_tank_BASE;
//**************************************

//data::main_game
//--------------------------------------
std::array<sfC::Text_t, 4> data::main_game::texts = {
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 35, sf::Vector2f(sfCON::WindowWidth * 0.508f, 30.f), "First car "),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 35, sf::Vector2f(sfCON::WindowWidth * 0.540f, 65.f), "0"),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 35, sf::Vector2f(sfCON::WindowWidth * 0.39f, 30.f), "Second car "),
    sfC::Text_t("../Fonts/nfs-mw3.ttf", 35, sf::Vector2f(sfCON::WindowWidth * 0.422f, 65.f), "0"),
};

sf::View data::main_game::view1(sf::FloatRect(0, 0, sfCON::WindowWidth * 0.48f, sfCON::WindowHeight));
sf::View data::main_game::view2(sf::FloatRect(0, 0, sfCON::WindowWidth * 0.48f, sfCON::WindowHeight));
sf::View data::main_game::full_view(sf::FloatRect(0, 0, sfCON::WindowWidth, sfCON::WindowHeight));

sfC::Picture_t data::main_game::mid_strip("../Images/strip.png", sf::IntRect(743, 0, sfCON::WindowWidth / 100, sfCON::WindowHeight), sf::Vector2f(sfCON::WindowWidth * 0.495f, 0.f));
sfC::Map data::main_game::map("../Images/blocks3.png");

sfC::Car_t data::main_game::tank1(&data::main_game::map, "../Images/cars.png", sf::IntRect(93, 268, 44, 78), sf::Vector2f(80.f, 80.f), sf::Color(255, 255, 255), 0.7f);
sfC::Car_t data::main_game::tank2(&data::main_game::map, "../Images/cars.png", sf::IntRect(93, 138, 44, 78), sf::Vector2f(80.f, 80.f), sf::Color(255, 255, 255), 0.7f);

bool data::main_game::read_map(const std::string &name, sfC::Map &cur_map /* = data::main_game::map*/)
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
//--------------------------------------

//  data::create_map
//++++++++++++++++++++++++++++++++++++++
sfC::Map data::create_map::map("../Images/blocks3.png");
sfC::Picture_t data::create_map::info_user("../Images/To_create_menu.png", sf::IntRect(243, 277, 180, 265), sf::Vector2f(10.f, 812.f), sf::Color::Magenta);

sf::View data::create_map::view(sf::FloatRect(0.f, 0.f, sfCON::WindowWidth, sfCON::WindowHeight));

std::map<data::create_map::data_for_keys, bool> data::create_map::keys;

std::stack<data::create_map::data_for_stack> data::create_map::actions;

sfC::BlockPrototype::TypeBlock data::create_map::cur_block = sfC::BlockPrototype::TypeBlock::Wall;

void data::create_map::update_mouse(int x, int y) noexcept
{
    if (x < sfCON::WindowWidth * 0.1f)
        data::create_map::keys[data::create_map::data_for_keys::Mouse_Left] = true;
    else
        data::create_map::keys[data::create_map::data_for_keys::Mouse_Left] = false;
    if (x > sfCON::WindowWidth * 0.85f)
        data::create_map::keys[data::create_map::data_for_keys::Mouse_Right] = true;
    else
        data::create_map::keys[data::create_map::data_for_keys::Mouse_Right] = false;
    if (y < sfCON::WindowHeight * 0.15f)
        data::create_map::keys[data::create_map::data_for_keys::Mouse_Up] = true;
    else
        data::create_map::keys[data::create_map::data_for_keys::Mouse_Up] = false;
    if (y > sfCON::WindowHeight * 0.80f)
        data::create_map::keys[data::create_map::data_for_keys::Mouse_Down] = true;
    else
        data::create_map::keys[data::create_map::data_for_keys::Mouse_Down] = false;
}
void data::create_map::update_block(const sf::Vector2i &block, sfC::BlockPrototype::TypeBlock type) noexcept
{
    sfC::BlockPrototype::TypeBlock old_type = data::create_map::map.get_type_block(block);

    if (data::create_map::map.change_block(block, type))
    {

        if (data::create_map::actions.empty())
        {
            data::create_map::actions.push(data::create_map::data_for_stack(block, old_type));
            return;
        }
        if (!data::create_map::actions.top().is_equal(block, type))
            data::create_map::actions.push(data::create_map::data_for_stack(block, old_type));
    }
}
void data::create_map::cancel_last_update() noexcept
{
    if (!data::create_map::actions.empty())
    {
        data::create_map::data_for_stack prev_block = data::create_map::actions.top();
        data::create_map::actions.pop();

        data::create_map::map.change_block(prev_block.block, prev_block.type);
    }
}
void data::create_map::move_view() noexcept
{
    data::create_map::view.move(
        sfCON::SPEED_CAMERA * data::create_map::keys[data::create_map::data_for_keys::Mouse_Right] - sfCON::SPEED_CAMERA * data::create_map::keys[data::create_map::data_for_keys::Mouse_Left],
        sfCON::SPEED_CAMERA * data::create_map::keys[data::create_map::data_for_keys::Mouse_Down] - sfCON::SPEED_CAMERA * data::create_map::keys[data::create_map::data_for_keys::Mouse_Up]);
}
void data::create_map::clear_stack() noexcept
{
    while (!data::create_map::actions.empty())
        data::create_map::actions.pop();
}
//++++++++++++++++++++++++++++++++++++++

//  data::map_prototypes
//======================================
std::vector<std::string> data::map_prototypes::maps;
constexpr char data::map_prototypes::main_file[];

bool data::map_prototypes::insert_map(const std::string &name, const sfC::MapPrototype &map)
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

void data::map_prototypes::write_map_into_file(const std::string &file, const sfC::MapPrototype &map)
{
    std::ofstream out(file, std::ios::out);

    map.dump_interrior(out);
    if (!out.good())
        ERROR("File wasn't writen down properly!");

    out.close();
}

void data::map_prototypes::write_name_new_map(const std::string &file)
{
    std::fstream cur_file(data::map_prototypes::main_file, std::ios::app);
    cur_file << file << std::endl;
    cur_file.close();
}
//======================================

//  data::text + data::set_map
//((((((((((((((((((((((((((((((((((((((
sfC::Picture_t data::text::background("../Images/Saving2.png", sf::IntRect(0, 0, sfCON::WindowWidth, sfCON::WindowHeight), sf::Vector2f(0.f, 0.f), sf::Color::Magenta);

sfC::Text_t data::text::main_text("../Fonts/nfs-mw3.ttf", 120, sf::Vector2f(sfCON::WindowWidth * 0.1f, sfCON::WindowHeight * 0.35f), "Create map");
sfC::Text_t data::text::addition_text("../Fonts/19413.ttf", 100, sf::Vector2f(sfCON::WindowWidth * 0.1f, sfCON::WindowHeight * 0.5f), "NAME: ");

sf::View data::text::view(sf::FloatRect(0.f, 0.f, sfCON::WindowWidth, sfCON::WindowHeight));

sfC::Text_t data::text::show_down_action1("../Fonts/19413.ttf", 120, sf::Vector2f(sfCON::WindowWidth * 0.05f, sfCON::WindowHeight * 0.44f));
sfC::Text_t data::text::show_down_action2("../Fonts/19413.ttf", 80, sf::Vector2f(sfCON::WindowWidth * 0.05f, sfCON::WindowHeight * 0.6f));

sfC::Text_t data::set_map::main_text("../Fonts/nfs-mw3.ttf", 100, sf::Vector2f(sfCON::WindowWidth * 0.1f, sfCON::WindowHeight * 0.25f), "Download map");

size_t data::set_map::cur_map = 0;
sfC::Text_t data::set_map::cur_text("../Fonts/19413.ttf", 200, sf::Vector2f(sfCON::WindowWidth * 0.1f, sfCON::WindowHeight * 0.5f), "");
sfC::Picture_t data::set_map::direct_back("../Images/direct.png", sf::IntRect(109, 22, -87, 59), sf::Vector2f(0.f, 0.f), sf::Color::White);
//((((((((((((((((((((((((((((((((((((((

//Prepare data
void prepare_data()
{
    sfDATA::MainMenu::prepare_data_main_menu();

    prepare_data_create_map();
    prepare_data_menu_cars();

    prepare_data_main_game();

    prepare_data_map_prot();
}

void prepare_data_menu_cars()
{
    for (auto &pic : data::menu_cars::buttons)
        pic.set_scale(1.6f, 1.6f);

    int texts_num = 0;
    for (auto &text : data::menu_cars::texts)
    {
        if (texts_num == 4 || texts_num == 5)
            text.set_color(sf::Color::Black);
        else
            text.set_color(sf::Color::Magenta);
        texts_num++;
    }

    for (auto &level : data::menu_cars::levels)
        level.set_color(sf::Color::Blue);

    sf::FloatRect car1 = data::menu_cars::car1.get_loc_bounds();
    sf::FloatRect car2 = data::menu_cars::car2.get_loc_bounds();
    data::menu_cars::car1.set_origin(car1.width / 2.f, car1.height / 2.f);
    data::menu_cars::car2.set_origin(car2.width / 2.f, car2.height / 2.f);
}

void prepare_data_main_game()
{
    data::main_game::read_map("Begin", data::main_game::map);

    for (auto &text : data::main_game::texts)
        text.set_color(sf::Color::Blue);

    data::main_game::tank1.rotate(180.f);
    data::main_game::tank2.rotate(180.f);

    data::main_game::view1.setViewport(sf::FloatRect(0.505f, 0.f, 0.495f, 1.f));
    data::main_game::view2.setViewport(sf::FloatRect(0.f, 0.f, 0.495f, 1.f));

    data::main_game::tank1.set_view(&data::main_game::view1);
    data::main_game::tank2.set_view(&data::main_game::view2);
}

void prepare_data_create_map()
{
    data::main_game::read_map("Begin", data::create_map::map);

    data::create_map::keys.insert(std::make_pair(data::create_map::data_for_keys::Button_Left, false));
    data::create_map::keys.insert(std::make_pair(data::create_map::data_for_keys::Ctrl, false));
    data::create_map::keys.insert(std::make_pair(data::create_map::data_for_keys::Z, false));
    data::create_map::keys.insert(std::make_pair(data::create_map::data_for_keys::Mouse_Down, false));
    data::create_map::keys.insert(std::make_pair(data::create_map::data_for_keys::Mouse_Up, false));
    data::create_map::keys.insert(std::make_pair(data::create_map::data_for_keys::Mouse_Right, false));
    data::create_map::keys.insert(std::make_pair(data::create_map::data_for_keys::Mouse_Left, false));
}

void prepare_data_map_prot()
{
    std::ifstream cur_file(data::map_prototypes::main_file, std::ios::in);
    if (cur_file.is_open())
    {
        while (!cur_file.eof())
        {
            std::string cur_str;
            cur_file >> cur_str;
            if (cur_str.empty())
                break;

            data::map_prototypes::maps.push_back(cur_str);
        }
    }
    else
        ERROR(std::string("Can't open the main file ") + data::map_prototypes::main_file);

    cur_file.close();

    data::set_map::cur_text.set_text(data::map_prototypes::maps.at(data::set_map::cur_map));

    data::text::main_text.set_color(sf::Color::Red);
    data::text::addition_text.set_color(sf::Color::Red);
    data::set_map::main_text.set_color(sf::Color::Red);
    data::set_map::cur_text.set_color(sf::Color::Red);
    data::text::show_down_action1.set_color(sf::Color::Red);
    data::text::show_down_action2.set_color(sf::Color::Red);
}