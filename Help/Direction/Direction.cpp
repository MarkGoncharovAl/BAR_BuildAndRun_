#include "Direction.hpp"

void sfC::Direction_t::CheckKeyboard(sf::Event::EventType event, sf::Keyboard::Key key, Type type)
{
    if (type == Type::Arrows)
    {
        if (event == sf::Event::KeyPressed)
        {
            switch (key)
            {
            case sf::Keyboard::Up:
                Up = Do::Pressed;
                break;
            case sf::Keyboard::Down:
                Down = Do::Pressed;
                break;
            case sf::Keyboard::Right:
                Right = Do::Pressed;
                break;
            case sf::Keyboard::Left:
                Left = Do::Pressed;
                break;
            default:
                break;
            }
        }

        else if (event == sf::Event::KeyReleased)
        {
            switch (key)
            {
            case sf::Keyboard::Up:
                Up = Do::Released;
                break;
            case sf::Keyboard::Down:
                Down = Do::Released;
                break;
            case sf::Keyboard::Right:
                Right = Do::Released;
                break;
            case sf::Keyboard::Left:
                Left = Do::Released;
                break;
            default:
                break;
            }
        }
    }

    else // type == Type::WASD
    {
        if (event == sf::Event::KeyPressed)
        {
            switch (key)
            {
            case sf::Keyboard::W:
                Up = Do::Pressed;
                break;
            case sf::Keyboard::S:
                Down = Do::Pressed;
                break;
            case sf::Keyboard::D:
                Right = Do::Pressed;
                break;
            case sf::Keyboard::A:
                Left = Do::Pressed;
                break;
            default:
                break;
            }
        }

        else if (event == sf::Event::KeyReleased)
        {
            switch (key)
            {
            case sf::Keyboard::W:
                Up = Do::Released;
                break;
            case sf::Keyboard::S:
                Down = Do::Released;
                break;
            case sf::Keyboard::D:
                Right = Do::Released;
                break;
            case sf::Keyboard::A:
                Left = Do::Released;
                break;
            default:
                break;
            }
        }
    }
}

void sfC::Direction_t::CopyActDirection(const sfC::Direction_t &that)
{
    if (that.GetUp() != Do::Nothing)
        Up = that.GetUp();
    if (that.GetDown() != Do::Nothing)
        Down = that.GetDown();
    if (that.GetRight() != Do::Nothing)
        Right = that.GetRight();
    if (that.GetLeft() != Do::Nothing)
        Left = that.GetLeft();
}