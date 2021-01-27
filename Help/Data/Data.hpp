#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <array>
#include <stack>
#include <map>
#include "../../Common_libs/Errors/Errors.hpp"
#include "../Help.hpp"
#include "../../Map/Map.hpp"
#include "../../Object/Object.hpp"
#include "../Picture/Picture.hpp"
#include "../../Actions/Actions.hpp"

void prepare_data();

void prepare_data_main_menu();
void prepare_data_create_map();
void prepare_data_menu_cars();
void prepare_data_main_game();
void prepare_data_map_prot();

struct data
{

    class main_menu
    {
        static sf::IntRect released;
        static sf::IntRect pressed;

        static int cur_press;

        static sfC::Picture_t main_pic;

        static std::array<sfC::Picture_t, 5> buttons;

        static sfC::Text_t texts[5];

        friend bool AnalyseMenu(sf::RenderWindow &window);
        friend bool MainMenu(sf::RenderWindow &window);
        friend void prepare_data_main_menu();
    };

    class menu_cars
    {
        static sfC::Picture_t main_pic;

        static std::string file_buttons;
        static sf::IntRect tex_rect;

        static std::array<sfC::Picture_t, 4> main_buttons;

        static std::array<sfC::Picture_t, 8> buttons;
        static std::array<sfC::Text_t, 6> texts;

        static std::array<sfC::Text_t, 8> levels;

        static sfC::Picture_t car1;
        static sfC::Picture_t car2;
        static sfC::MenuCars_t data;

        static sfC::ParamCar_t sort1;
        static sfC::ParamCar_t sort2;

        friend void Full_Restart();
        friend bool AnalyseMenuCars(sf::RenderWindow &);
        friend bool MenuCars(sf::RenderWindow &window);
        friend void prepare_data_menu_cars();
    };

    class main_game
    {
        static std::array<sfC::Text_t, 4> texts;

        static sfC::Picture_t mid_strip;

        static sf::View view1;
        static sf::View view2;
        static sf::View full_view;

        static sfC::Map map;

        static sfC::Car_t tank1;
        static sfC::Car_t tank2;

        //////////////////////
        //returns true if map was read succesfully
        //false in another case
        //////////////////////
        static bool read_map(const std::string &file, sfC::Map &cur_map = data::main_game::map);

        friend void Full_Restart();
        friend bool AnalyseGame(sf::RenderWindow &, float);
        friend bool MainGame(sf::RenderWindow &, const sfC::ParamCar_t &, const sfC::ParamCar_t &);
        friend bool CheckWin();
        friend void prepare_data_main_game();
        friend bool SetMap(sf::RenderWindow &window);
        friend bool AnalyseSetMap(sf::RenderWindow &);
        friend void PrepareCreateMap(sf::RenderWindow &, sfC::Map &);
        friend void prepare_data_create_map();
    };

    class create_map
    {
        static sfC::Map map;
        static sfC::Picture_t info_user;

        static sf::View view;

        enum class data_for_keys
        {
            Button_Left = 0,
            Ctrl,
            Z,
            S,
            Mouse_Up,
            Mouse_Down,
            Mouse_Right,
            Mouse_Left
        };
        static std::map<data::create_map::data_for_keys, bool> keys;

        struct data_for_stack
        {
            data_for_stack(const sf::Vector2i init_block, sfC::BlockPrototype::TypeBlock init_type)
                : block(init_block),
                  type(init_type)
            {
            }
            bool is_equal(const sf::Vector2i &other_block, sfC::BlockPrototype::TypeBlock other_type) const
            {
                if (block.x == other_block.x &&
                    block.y == other_block.y &&
                    type == other_type)
                    return true;
                return false;
            }
            sf::Vector2i block;
            sfC::BlockPrototype::TypeBlock type;
        };
        static std::stack<data_for_stack> actions;

        static sfC::BlockPrototype::TypeBlock cur_block;

        static void update_mouse(int x, int y) noexcept;
        static void update_block(const sf::Vector2i &block, sfC::BlockPrototype::TypeBlock type) noexcept;
        static void cancel_last_update() noexcept;
        static void move_view() noexcept;
        static void clear_stack() noexcept;

        friend bool CreateMap(sf::RenderWindow &window);
        friend bool AnalyseCreateMap(sf::RenderWindow &window);
        friend void prepare_data_create_map();
    };

    class map_prototypes
    {
    public:
        ////////////////////
        // return true if map was pushed
        // return false if stack is full
        ////////////////////
        static bool insert_map(const std::string &name, const sfC::MapPrototype &map);
        static void write_map_into_file(const std::string &file, const sfC::MapPrototype &map);
        static void write_name_new_map(const std::string &file);

    private:
        static constexpr char main_file[] = "../MapTiles/!FULL-DATA.txt";
        static std::vector<std::string> maps;
        static constexpr size_t max_size = 128;

        friend void prepare_data_map_prot();
        friend bool SetMap(sf::RenderWindow &);
        friend bool AnalyseSetMap(sf::RenderWindow &);
        friend bool AnalysePrepareCreateMap(sf::RenderWindow &);
    };

    class text
    {
        static sfC::Picture_t background;
        static sfC::Text_t main_text;
        static sfC::Text_t addition_text;
        static sf::View view;

        friend std::string Wait_Text_User(sf::RenderWindow &);
        friend void prepare_data_map_prot();
        friend bool AnalyseSetMap(sf::RenderWindow &, std::string &, sfC::Text_t &);
        friend bool SetMap(sf::RenderWindow &window);
        friend void PrepareCreateMap(sf::RenderWindow &, sfC::Map &);

        static sfC::Text_t show_down_action1;
        static sfC::Text_t show_down_action2;
        friend void ShowDoneAction(sf::RenderWindow &, const std::string &, const std::string &);
    };

    class set_map
    {
        static sfC::Text_t main_text;

        static size_t cur_map;
        static sfC::Text_t cur_text;

        static sfC::Picture_t direct_back;

        friend bool SetMap(sf::RenderWindow &);
        friend void prepare_data_map_prot();
        friend bool AnalyseSetMap(sf::RenderWindow &);
        friend void PrepareCreateMap(sf::RenderWindow &, sfC::Map &);
        friend bool AnalysePrepareCreateMap(sf::RenderWindow &);
    };
};
