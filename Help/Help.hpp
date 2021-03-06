#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Text/Text.hpp"
#include "Picture/Picture.hpp"
#include "ParamCar/ParamCar.hpp"
#include "FastDraw.hpp"

#include "DefinesFile.hpp"

namespace sfF
{

    bool IS_ASKII(const sf::Uint32 &symbol) noexcept;

    ///////////////////////////////////////////////
    // Rewrite digital in text
    // Example: str = '6', dist = 2
    // => str = '8'
    // Output=check, true is good
    ///////////////////////////////////////////////
    bool change_text_num(sfC::Text_t &str, int dist);
    bool change_text_num(std::string &str, int dist);

    ///////////////////////////////////////////////
    // Returns left-up position of view
    ///////////////////////////////////////////////
    sf::Vector2f get_view_position(const sf::View &view);
    float get_view_position_x(const sf::View &view);
    float get_view_position_y(const sf::View &view);
    bool AnalyseWait_Text_User (sfC::Window& window , std::string& text , sfC::Text_t& user_text);
    void SetDefaultView(sfC::Window& window);
    void ShowDoneAction(sfC::Window& window, std::string const& text1, std::string const& text2 = "");

} // namespace sfF

//-------------------------------------------------------------------

//CONSTANTS
namespace sfCON
{
    constexpr float _DEG_TO_RAD = 31415.f / 1800000.f;

    constexpr size_t WindowWidth = 1917;
    constexpr size_t WindowHeight = 1078;

    constexpr float SIZE_BLOCK = 32.f;

    constexpr float SPEED_CAMERA = 1.f;
    constexpr float SPEED_SAND = 0.98f;
    constexpr float SPEED_ACCEL = 1.01f;

    constexpr int SOLID_BLOCK = 256;

    constexpr int APROX_BLOCK_X = 1;

    constexpr float levels = 5.f;
    constexpr char levels_char = 5;

    constexpr ::sfC::ParamCar_t sort_tank_BASE{1.f / 2500.f, 1.f / 12.f, 1.f / 4.f, 1.f / 15.f, 2.f, 170.f, 0.999f};
    constexpr ::sfC::ParamCar_t sort_tank_IDEAL{1.f / 400.f, 1.5f, 1.f / 1.2f, 1.f / 5.f, 10.f, 20.f, 0.96f};

    constexpr float acceleration_tank_rank = (sort_tank_IDEAL.GetAcceleration() - sort_tank_BASE.GetAcceleration()) / levels;
    constexpr float back_speed_tank_rank = (sort_tank_IDEAL.GetBackCoef() - sort_tank_BASE.GetBackCoef()) / levels;
    constexpr float max_speed_tank_rank = (sort_tank_IDEAL.GetMaxSpeed() - sort_tank_BASE.GetMaxSpeed()) / levels;
    constexpr float rotate_tank_rank = (sort_tank_IDEAL.GetRotateSpeed() - sort_tank_BASE.GetRotateSpeed()) / levels;
    constexpr float max_rotate_tank_rank = (sort_tank_IDEAL.GetMaxRotSpeed() - sort_tank_BASE.GetMaxRotSpeed()) / levels;
    constexpr float controll_tank_rank = (sort_tank_IDEAL.GetDriftSpeed() - sort_tank_BASE.GetDriftSpeed()) / levels;
    constexpr float decell_tank_rank = (sort_tank_IDEAL.GetDeceleration() - sort_tank_BASE.GetDeceleration()) / levels;

    static const sfC::Picture_t Saving2PNG("../Images/Saving2.png" , sf::IntRect (0 , 0 , sfCON::WindowWidth , sfCON::WindowHeight) , sf::Vector2f (0.f , 0.f) , sf::Color::Magenta);
} // namespace sfCON