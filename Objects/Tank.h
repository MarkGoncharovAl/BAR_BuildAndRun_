#pragma once
#include <SFML/Graphics.hpp>
#include "../Map/Map.h"
#include <iostream>
#include <cmath>
#include "../Help/Help.hpp"
#include "../Common_libs/errors.hpp"

namespace O
{

    class Object
    {
    public:
        /////////////////////////////////////////////////////
        // Constructor
        // sf::Color mask - the mask of picture
        //     It means: sf::Image::CreateColorFromMask(mask);
        //     Use sf::Color() if nothing up to delete
        /////////////////////////////////////////////////////
        Object(M::Map *map, const std::string &file, const sf::IntRect &rect, const sf::Vector2f &coord, const sf::Color &mask, float scale);
        /////////////////////////////////////////////////////
        // Fast function, used for drawing
        // Application:
        // sf::RenderWindow::draw (Object::for_draw());
        /////////////////////////////////////////////////////
        inline const sf::Sprite &for_draw() const noexcept { return sprite_; }

        /////////////////////////////////////////////////////
        // Just return position on the map (NOT VIEW)
        /////////////////////////////////////////////////////
        inline const sf::Vector2f &get_position() const noexcept { return sprite_.getPosition(); }

        /////////////////////////////////////////////////////
        // rotate object (degree isn't rad!)
        // moving clockwise
        /////////////////////////////////////////////////////
        bool rotate(float degree);

        /////////////////////////////////////////////////////
        // Move object in the direction of object
        // That's why there's no reason to worry about direction
        /////////////////////////////////////////////////////
        bool move(float dist);

        /////////////////////////////////////////////////////
        // Now just move object to the first location
        /////////////////////////////////////////////////////
        void restart() noexcept;

        /////////////////////////////////////////////////////
        // Check:
        // If object is free (used M::Map::is_solid())
        /////////////////////////////////////////////////////
        bool is_free() const noexcept;

        bool is_sand() const noexcept;
        bool is_accel() const noexcept;
        bool is_restart() const noexcept;

        inline sf::FloatRect get_boundaries() const noexcept { return sprite_.getGlobalBounds(); }

    protected:
        sf::Image image_;
        sf::Texture texture_;
        sf::Sprite sprite_;

        sf::Vector2f size_;
        sf::Vector2f coord_;
        M::Map *map_;
    };

    class Bullet : public Object
    {
    public:
        //Bullet(M::Map* map, const sort_bull& cur_sort, const std::string& file, const sf::IntRect& rect, const sf::Vector2f& coord, const sf::Color& color);

    private:
        const sort_bull cur_sort_;
    };

    class Tank : public Object
    {
    public:
        Tank(sf::View *view, M::Map *map, const sfC::ParamCar_t &cur_sort_tank, const std::string &file, const sf::IntRect &rect, const sf::Vector2f &coord, const sf::Color &color, float scale = 1.f) noexcept;
        Tank(M::Map *map, const std::string &file, const sf::IntRect &rect, const sf::Vector2f &coord, const sf::Color &color, float scale = 1.f) noexcept;

        /////////////////////////////////////////////////////
        // Analyse moving of tank
        // CharRect movings - waited for actions that was translated from the Keyboard
        //     -1 - Button (Up, Down...) was released right now
        //      0 - Button have the same state
        //      1 - Button was pressed right now
        /////////////////////////////////////////////////////
        bool move_tank(const CharRect &movings, float time);
        void stop_moving() noexcept;

        inline void set_view(sf::View *init_view) noexcept { view_ = init_view; }
        inline void set_sort(const sfC::ParamCar_t &init_sort) noexcept { cur_sort_ = init_sort; }

    private:
        sfC::ParamCar_t cur_sort_;
        float drifting_;
        float speed_;
        CharRect motion_;
        sf::View *view_;
    };

} // namespace O

void RestartTank(O::Tank &tank);