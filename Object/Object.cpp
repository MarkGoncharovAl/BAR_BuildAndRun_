#include "Object.hpp"

sfC::Object_t::Object_t(sfC::Map *map, const std::string &file, const sf::IntRect &rect, const sf::Vector2f &coord, const sf::Color &color, float scale)
    : image_(),

      texture_(),
      sprite_(),

      size_(static_cast<float>(rect.width), static_cast<float>(rect.height)),
      coord_(coord),
      map_(map)

{
    if (!image_.loadFromFile(file))
    {
        LOG_error << "Can't find a file for object: " << file;
        exit(1);
    }

    image_.createMaskFromColor(color);

    texture_.loadFromImage(image_);

    sprite_.setTexture(texture_);
    sprite_.setTextureRect(rect);
    sprite_.setPosition(coord);

    sprite_.setOrigin(sprite_.getLocalBounds().width / 2.f, sprite_.getLocalBounds().height / 2.f);

    //scale object and its size
    sprite_.setScale(scale, scale);
    size_.x *= scale;
    size_.y *= scale;
}

bool sfC::Object_t::rotate(float degree)
{
    sprite_.rotate(degree);
    return true;
}
bool sfC::Object_t::move(float dist)
{
    float rotation = sprite_.getRotation();
    sprite_.move(dist * sin(rotation * sfCON::_DEG_TO_RAD), -1 * dist * cos(rotation * sfCON::_DEG_TO_RAD));
    return true;
}
void sfC::Object_t::restart()
{
    sprite_.setPosition(coord_);
    sprite_.setRotation(180.f);
}

bool sfC::Object_t::is_free() const
{
    float cosin = cos(sprite_.getRotation() * sfCON::_DEG_TO_RAD);
    float sinus = sin(sprite_.getRotation() * sfCON::_DEG_TO_RAD);

    sf::Vector2f left_top(0.5f * (size_.y * sinus - size_.x * cosin) + sprite_.getPosition().x,
                          -0.5f * (size_.x * sinus + size_.y * cosin) + sprite_.getPosition().y);

    sf::Vector2f coef(size_.x * cosin * 0.2f, size_.x * sinus * 0.2f);

    for (int i = 0; i < 5; ++i)
    {
        if (map_->is_solid(left_top))
        {
            return false;
        }
        left_top.x += coef.x;
        left_top.y += coef.y;
    }

    coef.x = -1.f * size_.y * sinus * 0.2f;
    coef.y = size_.y * cosin * 0.2f;
    for (int i = 0; i < 5; ++i)
    {
        if (map_->is_solid(left_top))
            return false;
        left_top.x += coef.x;
        left_top.y += coef.y;
    }
    //printf("Cur: %g %g\tBase^ %g %g\n", left_top.x, left_top.y, sprite_.getPosition().x, sprite_.getPosition().y);

    coef.x = -1.f * size_.x * cosin * 0.2f;
    coef.y = -1.f * size_.x * sinus * 0.2f;
    for (int i = 0; i < 5; ++i)
    {
        if (map_->is_solid(left_top))
            return false;
        left_top.x += coef.x;
        left_top.y += coef.y;
    }

    coef.x = size_.y * sinus * 0.2f;
    coef.y = -1.f * size_.y * cosin * 0.2f;
    for (int i = 0; i < 5; ++i)
    {
        if (map_->is_solid(left_top))
            return false;
        left_top.x += coef.x;
        left_top.y += coef.y;
    }

    return true;
}

sfC::Car_t::Car_t(sf::View *view, sfC::Map *map, const sfC::ParamCar_t &cur_sort_tank, const std::string &file, const sf::IntRect &rect, const sf::Vector2f &coord, const sf::Color &color, float scale)
    : Object_t(map, file, rect, coord, color, scale),
      cur_sort_(cur_sort_tank),
      drifting_(0),
      speed_(0),
      motion_(),
      view_(view)
{
}

sfC::Car_t::Car_t(sfC::Map *map, const std::string &file, const sf::IntRect &rect, const sf::Vector2f &coord, const sf::Color &color, float scale)
    : Object_t(map, file, rect, coord, color, scale),
      cur_sort_(),
      drifting_(0),
      speed_(0),
      motion_(),
      view_(nullptr)
{
}

//DO THIS
bool sfC::Car_t::move_car(const sfC::Direction_t &movings, float time)
{
    using Action = sfC::Direction_t::Do;
    motion_.CopyActDirection(movings);

    //!Speed
    ///////////////////////////////////////////////////
    if (motion_.GetUp() == Action::Pressed)
        speed_ += cur_sort_.GetAcceleration();
    if (motion_.GetDown() == Action::Pressed)
        speed_ -= cur_sort_.GetBackCoef() * cur_sort_.GetAcceleration();

    if (motion_.GetUp() == Action::Released && motion_.GetDown() == Action::Released)
        speed_ *= cur_sort_.GetDeceleration();

    if (speed_ > cur_sort_.GetMaxSpeed())
        speed_ = cur_sort_.GetMaxSpeed();

    if (speed_ < -1 * cur_sort_.GetBackCoef() * cur_sort_.GetMaxSpeed())
        speed_ = -1 * cur_sort_.GetBackCoef() * cur_sort_.GetMaxSpeed();
    ///////////////////////////////////////////////////

    //!Rotation
    ///////////////////////////////////////////////////
    if (motion_.GetRight() == Action::Pressed)
        drifting_ += cur_sort_.GetRotateSpeed();
    if (motion_.GetLeft() == Action::Pressed)
        drifting_ -= cur_sort_.GetRotateSpeed();

    if (motion_.GetLeft() == Action::Released && motion_.GetRight() == Action::Released)
        drifting_ *= cur_sort_.GetDeceleration();

    if (drifting_ > cur_sort_.GetRotateSpeed())
        drifting_ = cur_sort_.GetRotateSpeed();
    if (drifting_ < -1 * cur_sort_.GetRotateSpeed())
        drifting_ = -1 * cur_sort_.GetRotateSpeed();

    const float current_extra_rot = cur_sort_.GetDriftSpeed() * speed_ * drifting_ * time;
    const sf::Vector2f prev_pos = sprite_.getPosition();
    const float deg = sprite_.getRotation();

    rotate(-1 * current_extra_rot);
    move(speed_ * time);
    rotate(current_extra_rot + drifting_ * time);

    if (!this->is_free())
    {
        drifting_ = 0.f;
        speed_ *= -0.5f;
        sprite_.setPosition(prev_pos);
        sprite_.setRotation(deg);
    }

    if (this->is_sand())
    {
        speed_ *= sfCON::SPEED_SAND;
    }
    else if (this->is_accel())
    {
        speed_ *= sfCON::SPEED_ACCEL;
    }
    else if (this->is_restart())
    {
        sfF::RestartCar(*this);
    }

    view_->setCenter(round(sprite_.getPosition().x), round(sprite_.getPosition().y));
    return true;
}

void sfC::Car_t::stop_moving() noexcept
{
    drifting_ = 0.f;
    speed_ = 0.f;
}

void sfF::RestartCar(sfC::Car_t &car)
{
    car.restart();
    car.stop_moving();
}