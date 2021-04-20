#pragma once

#include <iostream>
#include <stack>
#include <SFML/Graphics.hpp>
#include "../Map/Map.hpp"
#include "../Help/Picture/Picture.hpp"
#include "../Help/FastDraw.hpp"

namespace sfDATA
{
    class CreateMap_t
    {
    public:
        static void PrepareData ();
        static bool AnalyseCreateMap (sfC::Window& window);
        static bool CreateMap (sfC::Window& window);

    private:
        static sfC::Map map;
        static sfC::Picture_t info_user;

        static sf::View view;

        enum class data_for_keys
        {
            Button_Left = 0 ,
            Ctrl ,
            Z ,
            S ,
            Mouse_Up ,
            Mouse_Down ,
            Mouse_Right ,
            Mouse_Left
        };
        static std::map<sfDATA::CreateMap_t::data_for_keys , bool> keys;

        struct data_for_stack
        {
            data_for_stack (const sf::Vector2i init_block , sfC::BlockPrototype::TypeBlock init_type)
                : block (init_block) ,
                type (init_type)
            {}
            bool is_equal (const sf::Vector2i& other_block , sfC::BlockPrototype::TypeBlock other_type) const
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

        static void update_mouse (int x , int y) noexcept;
        static void update_block (const sf::Vector2i& block , sfC::BlockPrototype::TypeBlock type) noexcept;
        static void cancel_last_update () noexcept;
        static void move_view () noexcept;
        static void clear_stack () noexcept;
    };
}