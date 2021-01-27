#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>
#include "../../Common_libs/Errors/Errors.hpp"

namespace sfC
{

    struct MenuCars_t final
    {
        MenuCars_t() = default;

        //////////////////////////////
        // Returns to basic settings
        //////////////////////////////
        void restart();

        int pos_left = 0;
        int pos_right = 0;

        std::array<char, 4> lvl_left = {0};
        std::array<char, 4> lvl_right = {0};
    };

    class ParamCar_t final
    {
    public:
        constexpr ParamCar_t() noexcept = default;
        constexpr ParamCar_t(const ParamCar_t &other) noexcept = default;
        constexpr ParamCar_t(float acc, float back_c, float m_sp, float rot_sp, float m_rot, float dr_sp, float dec) noexcept
            : acceleration_(acc),
              back_coef_(back_c),
              max_speed_(m_sp),
              rotate_speed_(rot_sp),
              max_rot_speed_(m_rot),
              drift_speed_(dr_sp),
              deceleration_(dec)
        {
        }

        constexpr float GetAcceleration() const noexcept { return acceleration_; }
        constexpr float GetBackCoef() const noexcept { return back_coef_; }
        constexpr float GetMaxSpeed() const noexcept { return max_speed_; }
        constexpr float GetRotateSpeed() const noexcept { return rotate_speed_; }
        constexpr float GetMaxRotSpeed() const noexcept { return max_rot_speed_; }
        constexpr float GetDriftSpeed() const noexcept { return drift_speed_; }
        constexpr float GetDeceleration() const noexcept { return deceleration_; }

        ///////////////////////////////////////////
        // Correcting data of statistic of car
        ///////////////////////////////////////////
        enum class Do
        {
            Increase,
            Decrease
        };
        void CorrectProperties(int property, Do action = Do::Increase);

    private:
        float acceleration_ = 0.f;
        float back_coef_ = 0.f;
        float max_speed_ = 0.f;
        float rotate_speed_ = 0.f;
        float max_rot_speed_ = 0.f;
        float drift_speed_ = 0.f;
        float deceleration_ = 0.f;
    };

} // namespace sfC