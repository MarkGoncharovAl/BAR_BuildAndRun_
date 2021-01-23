#include "Picture.hpp"

sfC::Picture_t::Picture_t(const std::string &file, const sf::IntRect &tex_rect, const sf::Vector2f &coord, const sf::Color &mask /* = sf::Color()*/, const sf::Vector2f &scale /* = sf::Vector2f(1.f, 1.f)*/)
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