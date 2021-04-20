#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../../Common_libs/Errors/Errors.hpp"

/////////////////////////////////////////////////////
// Better way to use sf::Font and sf::Text together
/////////////////////////////////////////////////////
namespace sfC
{
    class Text_t final
    {
    public:
        Text_t(const std::string &file, unsigned int size, const sf::Vector2f &pos, const std::string &str = "");

        std::string get_text() const { return text_.getString(); }

        /////////////////////////////////////////////////////
        // Changing current text
        /////////////////////////////////////////////////////
        void set_text(const std::string &text) { text_.setString(text); }
        void push_back(const char cur_sym) { text_.setString(text_.getString() + cur_sym); }
        void pop_back();

        /////////////////////////////////////////////////////
        // Change current style of text
        // Use sf::Style::(new_style)
        /////////////////////////////////////////////////////
        void set_style(const sf::Uint32 &new_style) { text_.setStyle(new_style); }

        /////////////////////////////////////////////////////
        // Just change color
        // Can be used with base colors, such as sf::Color::Red
        // And complexity with sf::Color object(pix1, pix2, pix3), where
        //      pix - the color of the base: Red, Blue, Green
        /////////////////////////////////////////////////////
        void set_color(const sf::Color &new_color) { text_.setFillColor(new_color); }
        /////////////////////////////////////////////////////
        // Fast function, used for drawing
        // Application:
        // sf::RenderWindow::draw (Text::for_draw());
        /////////////////////////////////////////////////////
        const sf::Text &for_draw() const { return text_; }

        explicit operator bool () const noexcept { return !text_.getString().isEmpty(); }

    private:
        sf::Font font_;
        sf::Text text_;
    };

} // namespace sfC