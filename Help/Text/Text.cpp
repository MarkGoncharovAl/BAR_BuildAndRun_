#include "Text.hpp"

sfC::Text_t::Text_t (const std::string& file , unsigned int size , const sf::Vector2f& pos , const std::string& str /*= ""*/)
    : font_ () ,
    text_ ()
{
    if (!font_.loadFromFile (file))
    {
        LOG_error << ("Can't load text!");
        exit (1);
    }
    text_.setCharacterSize (size);
    text_.setFont (font_);
    text_.setString (str);
    text_.setPosition (pos);
}

void sfC::Text_t::pop_back ()
{
    std::string temp = text_.getString ();
    if (!temp.empty ())
    {
        temp.pop_back ();
        text_.setString (temp);
    }
}