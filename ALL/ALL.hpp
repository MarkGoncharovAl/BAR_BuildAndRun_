#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <array>
#include <memory>
#include "../Map/Map.hpp"
#include "../Object/Object.hpp"
#include "../Help/Picture/Picture.hpp"
#include "../Help/Help.hpp"
#include "../Help/Direction/Direction.hpp"
#include <stack>

namespace sfDATA
{
    void Full_Restart();
    void PrepareData();

} // namespace sfDATA

/////////////////////////////////////////////////////
// Check the user actions in the game
// Returns false - if game was closen or ended
//         true  - game is working now
/////////////////////////////////////////////////////
bool AnalyseGame(sf::RenderWindow &window, float time);

/////////////////////////////////////////////////////
// Create the game
// Returns false - if game was closen or ended
//         true  - never now))
/////////////////////////////////////////////////////
bool MainGame(sf::RenderWindow &window, const sfC::ParamCar_t &sort1, const sfC::ParamCar_t &sort2);

/////////////////////////////////////////////////////
// Check: user reached the goal or not
// Return false - if game isn't over
//        true  - target was achieved
/////////////////////////////////////////////////////
bool CheckWin();

/////////////////////////////////////////////////////
// Reset map
// Count_blocks - how many solid blocks your map will have
/////////////////////////////////////////////////////

void change_data_cars(sfC::ParamCar_t &sort, int proper, sfC::ParamCar_t::Do action = sfC::ParamCar_t::Do::Increase);

void ShowDoneAction(sf::RenderWindow &window, const std::string &info, const std::string &info2 = std::string());

namespace sfDATA
{

    class MainMenu_t
    {
    public:
        /////////////////////////////////////////////////////
        // Check the user actions in the menu
        // Returns false - if it's time to close menu
        //         true  - user didn't make a choise
        /////////////////////////////////////////////////////
        static bool AnalyseMenu(sf::RenderWindow &window);

        /////////////////////////////////////////////////////
        // Create main menu
        // Returns false - if menu was closen
        //         true  - never now))
        /////////////////////////////////////////////////////
        static bool MainMenu(sf::RenderWindow &window);

        static void PrepareData();

    private:
        static sf::IntRect released_;
        static sf::IntRect pressed_;

        static constexpr int count_buttons_ = 5;
        enum type_button_ : int
        {
            GAME = 0,
            RESTART,
            SET,
            CREATE,
            EXIT
        };
        static int cur_press_;

        static sfC::Picture_t main_pic_;

        static std::array<sfC::Picture_t, count_buttons_> buttons_;
        static std::array<sfC::Text_t, count_buttons_> texts_;

        /////////////////////
        // Returns false if function should be ended
        // if (!ActionPress(...)) return ...
        /////////////////////
        static bool ActionPress(sf::RenderWindow &window, int press);
    };

} // namespace sfDATA

bool AnalyseWait_Text_User(sf::RenderWindow &window, std::string &text, sfC::Text_t &user_text);

bool AnalyseSetMap(sf::RenderWindow &window);
bool SetMap(sf::RenderWindow &window);

bool AnalysePrepareCreateMap(sf::RenderWindow &window);
void PrepareCreateMap(sf::RenderWindow &window, sfC::Map &map);

bool AnalyseCreateMap(sf::RenderWindow &window);
bool CreateMap(sf::RenderWindow &window);

namespace sfDATA
{

    class MenuCars_t
    {
    public:
        static void Restart();
        /////////////////////////////////////////////////////
        // Menu where user can create a car
        /////////////////////////////////////////////////////
        static bool AnalyseMenuCars(sf::RenderWindow &);
        /////////////////////////////////////////////////////
        // Menu where user can create a car
        /////////////////////////////////////////////////////
        static bool MenuCars(sf::RenderWindow &window);

        static void PrepareData();

    private:
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
    };

    class MainGame_t
    {
    public:
        static void Restart();
        static void PrepareData(sfC::Map &create_map);

    private:
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
        static bool read_map(const std::string &file, sfC::Map &cur_map = sfDATA::MainGame_t::map);

        friend bool ::AnalyseGame(sf::RenderWindow &, float);
        friend bool ::MainGame(sf::RenderWindow &, const sfC::ParamCar_t &, const sfC::ParamCar_t &);
        friend bool ::CheckWin();
        friend bool ::SetMap(sf::RenderWindow &window);
        friend bool ::AnalyseSetMap(sf::RenderWindow &);
        friend void ::PrepareCreateMap(sf::RenderWindow &, sfC::Map &); //!
    };

    class CreateMap_t
    {
    public:
        static void PrepareData();

    private:
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
        static std::map<sfDATA::CreateMap_t::data_for_keys, bool> keys;

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

        friend bool ::CreateMap(sf::RenderWindow &window);
        friend bool ::AnalyseCreateMap(sf::RenderWindow &window);
    };

    class MapPrototypes_t
    {
    public:
        ////////////////////
        // return true if map was pushed
        // return false if stack is full
        ////////////////////
        static bool insert_map(const std::string &name, const sfC::MapPrototype &map);
        static void write_map_into_file(const std::string &file, const sfC::MapPrototype &map);
        static void write_name_new_map(const std::string &file);

        static void PrepareData();

    private:
        static constexpr char main_file[] = "../MapTiles/!FULL-DATA.txt";
        static std::vector<std::string> maps;
        static constexpr size_t max_size = 128;

        friend bool ::SetMap(sf::RenderWindow &);
        friend bool ::AnalyseSetMap(sf::RenderWindow &);
        friend bool ::AnalysePrepareCreateMap(sf::RenderWindow &);
    };

    class Text_t
    {
    public:
        static void PrepareData();
        static std::string WaitTextUser(sf::RenderWindow &window);

    private:
        static sfC::Picture_t background;
        static sfC::Text_t main_text;
        static sfC::Text_t addition_text;
        static sf::View view;

        friend bool AnalyseSetMap(sf::RenderWindow &, std::string &, sfC::Text_t &);
        friend bool ::SetMap(sf::RenderWindow &window);
        friend void ::PrepareCreateMap(sf::RenderWindow &, sfC::Map &);

        static sfC::Text_t show_down_action1;
        static sfC::Text_t show_down_action2;
        friend void ::ShowDoneAction(sf::RenderWindow &, const std::string &, const std::string &);
    };

    class SetMap_t
    {
    public:
        static void PrepareData(std::vector<std::string> &maps);

    private:
        static sfC::Text_t main_text;

        static size_t cur_map;
        static sfC::Text_t cur_text;

        static sfC::Picture_t direct_back;

        friend bool ::SetMap(sf::RenderWindow &);
        friend bool ::AnalyseSetMap(sf::RenderWindow &);
        friend void ::PrepareCreateMap(sf::RenderWindow &, sfC::Map &);
        friend bool ::AnalysePrepareCreateMap(sf::RenderWindow &);
    };
} // namespace sfDATA