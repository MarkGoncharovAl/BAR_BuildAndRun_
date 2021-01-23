#include "Help.hpp"

namespace sfF
{
    bool IS_ASKII(const sf::Uint32 &symbol)
    {
        return (symbol > 47 && symbol < 58) ||
               (symbol > 64 && symbol < 91) ||
               (symbol > 96 && symbol < 123) ||
               symbol == 95;
    }

    bool change_text_num(sfC::Text_t &str, int dist)
    {
        str.set_text(std::to_string(stoi(str.get_text()) + dist));
        if (str.get_text().empty())
            return false;
        return true;
    }

    bool change_text_num(std::string &str, int dist)
    {
        str = std::to_string(stoi(str) + dist);
        if (str.empty())
            return false;
        return true;
    }

    sf::Vector2f get_view_position(const sf::View &view)
    {
        return sf::Vector2f(view.getCenter().x - view.getSize().x / 2.f,
                            view.getCenter().y - view.getSize().y / 2.f);
    }

    float get_view_position_x(const sf::View &view)
    {
        return view.getCenter().x - view.getSize().x / 2.f;
    }

    float get_view_position_y(const sf::View &view)
    {
        return view.getCenter().y - view.getSize().y / 2.f;
    }

} // namespace sfF