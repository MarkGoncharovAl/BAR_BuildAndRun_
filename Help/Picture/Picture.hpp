#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../Common_libs/Errors/Errors.hpp"

namespace sfC
{
    class Picture_t final
    {
    public:
        /////////////////////////////////////////////////////
        // Constructor
        /////////////////////////////////////////////////////
        Picture_t(const std::string &file, const sf::IntRect &tex_rect, const sf::Vector2f &coord, const sf::Color &mask = sf::Color(), const sf::Vector2f &scale = sf::Vector2f(1.f, 1.f))
            : image_(),
              texture_(),
              sprite_()
        {
            if (!image_.loadFromFile(file))
                ERROR(std::string("Can't find a file for object: ") + file);

            image_.createMaskFromColor(mask);
            texture_.loadFromImage(image_);

            sprite_.setTexture(texture_);
            sprite_.setTextureRect(tex_rect);
            sprite_.setPosition(coord);

            sprite_.setScale(scale);
        }
        /////////////////////////////////////////////////////
        // Fast function, used for drawing
        // Application:
        // sf::RenderWindow::draw (Picture_::for_draw());
        /////////////////////////////////////////////////////
        const sf::Sprite &for_draw() const { return sprite_; }

        /////////////////////////////////////////////////////
        // Getting sf::Sprite::getTextureRect() of object
        /////////////////////////////////////////////////////
        const sf::IntRect &get_rect() const { return sprite_.getTextureRect(); }

        /////////////////////////////////////////////////////
        // Returns rectangle of an object
        /////////////////////////////////////////////////////
        sf::FloatRect get_loc_bounds() const { return sprite_.getLocalBounds(); }
        sf::FloatRect get_glob_bounds() const { return sprite_.getGlobalBounds(); }

        /////////////////////////////////////////////////////
        // Settings
        /////////////////////////////////////////////////////
        void set_texture(const sf::IntRect &tex) { sprite_.setTextureRect(tex); }
        void set_origin(float x, float y) { sprite_.setOrigin(x, y); }
        void set_scale(float x, float y) { sprite_.scale(x, y); }
        void set_position(float x, float y) { sprite_.setPosition(x, y); }
        void move(float x, float y) { sprite_.move(x, y); }
        void rotate(float x) { sprite_.rotate(x); }

        /////////////////////////////////////////////////////
        // Checking contains of coordinate in object
        /////////////////////////////////////////////////////
        bool is_include(const sf::Vector2f &coords) const { return sprite_.getGlobalBounds().contains(coords); }
        bool is_include(float x, float y) const { return sprite_.getGlobalBounds().contains(x, y); }
        bool is_include(int x, int y) const { return sprite_.getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y)); }

    private:
        sf::Image image_;
        sf::Texture texture_;
        sf::Sprite sprite_;
    };

} // namespace sfC