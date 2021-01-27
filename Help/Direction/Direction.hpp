#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace sfC
{

    class Direction_t final
    {
    public:
        enum class Do
        {
            Pressed,
            Nothing,
            Released
        };
        enum class Type
        {
            WASD,
            Arrows
        };

        constexpr Direction_t() noexcept = default;
        Direction_t(const Direction_t &other) noexcept = default;

        void CheckKeyboard(sf::Event::EventType event, sf::Keyboard::Key key, Type type);

        ///////////////////////////////////////////////
        //  Copying actions on Direction. Use if you did read!
        ///////////////////////////////////////////////
        void CopyActDirection(const sfC::Direction_t &that);

        constexpr Do GetUp() const noexcept { return Up; }
        constexpr Do GetDown() const noexcept { return Down; }
        constexpr Do GetRight() const noexcept { return Right; }
        constexpr Do GetLeft() const noexcept { return Left; }

    private:
        Do Up = Do::Nothing;
        Do Down = Do::Nothing;
        Do Right = Do::Nothing;
        Do Left = Do::Nothing;
    };

} // namespace sfC