#include "ParamCar.hpp"
#include "../Help.hpp"

void sfC::MenuCars_t::restart()
{
    pos_left = 0;
    pos_right = 0;

    std::for_each(lvl_left.begin(), lvl_left.end(), [](char &it) { it = 0; });
    std::for_each(lvl_right.begin(), lvl_right.end(), [](char &it) { it = 0; });
}

void sfC::ParamCar_t::CorrectProperties(int property, Do action /* = Do::Increase*/)
{
    switch (action)
    {
    case Do::Increase:
        switch (property)
        {
        case 0:
            acceleration_ += CON::acceleration_tank_rank;
            break;
        case 1:
            max_speed_ += CON::max_speed_tank_rank;
            back_coef_ += CON::back_speed_tank_rank;
            break;
        case 2:
            rotate_speed_ += CON::rotate_tank_rank;
            max_rot_speed_ += CON::max_rotate_tank_rank;
            break;
        case 3:
            deceleration_ += CON::decell_tank_rank;
            drift_speed_ += CON::controll_tank_rank;
            break;
        default:
            WARNING("Can't find such property!");
            break;
        }

        break;

    case Do::Decrease:

        switch (property)
        {
        case 0:
            acceleration_ -= CON::acceleration_tank_rank;
            break;
        case 1:
            max_speed_ -= CON::max_speed_tank_rank;
            back_coef_ -= CON::back_speed_tank_rank;
            break;
        case 2:
            rotate_speed_ -= CON::rotate_tank_rank;
            max_rot_speed_ -= CON::max_rotate_tank_rank;
            break;
        case 3:
            deceleration_ -= CON::decell_tank_rank;
            drift_speed_ -= CON::controll_tank_rank;
            break;
        default:
            WARNING("Can't find such property!");
            break;
        }

        break;

    default:
        WARNING("Can't change properties!");
        break;
    }
}