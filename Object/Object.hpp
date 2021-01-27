#pragma once

#include <SFML/Graphics.hpp>
#include "../Map/Map.hpp"
#include <iostream>
#include <cmath>
#include "../Help/Help.hpp"
#include "../Common_libs/Errors/Errors.hpp"
#include "../Help/Direction/Direction.hpp"

namespace sfC
{
    class Object_t
    {
    public:
        /////////////////////////////////////////////////////
        // Constructor
        // sf::Color mask - the mask of picture
        //     It means: sf::Image::CreateColorFromMask(mask);
        //     Use sf::Color() if nothing up to delete
        /////////////////////////////////////////////////////
        Object_t(sfC::Map *map, const std::string &file, const sf::IntRect &rect, const sf::Vector2f &coord, const sf::Color &mask, float scale);

        /////////////////////////////////////////////////////
        // Fast function, used for drawing
        // Application:
        // sf::RenderWindow::draw (Object::for_draw());
        /////////////////////////////////////////////////////
        const sf::Sprite &for_draw() const { return sprite_; }

        /////////////////////////////////////////////////////
        // Just return position on the map (NOT VIEW)
        /////////////////////////////////////////////////////
        sf::Vector2f get_position() const { return sprite_.getPosition(); }

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
        void restart();

        /////////////////////////////////////////////////////
        // Check:
        // If object is free (used M::Map::is_solid())
        /////////////////////////////////////////////////////
        bool is_free() const;

        bool is_sand() const { return map_->is_sand(sprite_.getPosition()); }
        bool is_accel() const { return map_->is_accel(sprite_.getPosition()); }
        bool is_restart() const { return map_->is_restart(sprite_.getPosition()); }

        sf::FloatRect get_boundaries() const { return sprite_.getGlobalBounds(); }

    protected:
        sf::Image image_;
        sf::Texture texture_;
        sf::Sprite sprite_;

        sf::Vector2f size_;
        sf::Vector2f coord_;
        sfC::Map *map_;
    };

    class Car_t : public Object_t
    {
    public:
        Car_t(sf::View *view, sfC::Map *map, const sfC::ParamCar_t &cur_sort_tank, const std::string &file, const sf::IntRect &rect, const sf::Vector2f &coord, const sf::Color &color, float scale = 1.f);
        Car_t(sfC::Map *map, const std::string &file, const sf::IntRect &rect, const sf::Vector2f &coord, const sf::Color &color, float scale = 1.f);

        /////////////////////////////////////////////////////
        // Analyse moving of tank
        // sfC::Direction_t - waited for actions that was translated from the Keyboard
        /////////////////////////////////////////////////////
        bool move_car(const sfC::Direction_t &movings, float time);
        void stop_moving() noexcept;

        void set_view(sf::View *init_view) { view_ = init_view; }
        void set_sort(const sfC::ParamCar_t &init_sort) { cur_sort_ = init_sort; }

    private:
        sfC::ParamCar_t cur_sort_;
        float drifting_;
        float speed_;
        sfC::Direction_t motion_;
        sf::View *view_;
    };

} // namespace sfC

namespace sfF
{
    void RestartCar(sfC::Car_t &car);
}