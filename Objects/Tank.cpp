#include "Tank.h"

O::Object::Object(M::Map *map, const std::string &file, const sf::IntRect &rect, const sf::Vector2f &coord, const sf::Color &color, float scale)
    : image_(),

      texture_(),
      sprite_(),

      size_(static_cast<float>(rect.width), static_cast<float>(rect.height)),
      coord_(coord),
      map_(map)
{
    if (!image_.loadFromFile(file))
    {
        ERROR(std::string("Can't find a file for object: ") + file);
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

bool O::Object::rotate(float degree)
{
    sprite_.rotate(degree);
    return true;
}
bool O::Object::move(float dist)
{
    float rotation = sprite_.getRotation();
    sprite_.move(dist * sin(rotation * CON::_DEG_TO_RAD), -1 * dist * cos(rotation * CON::_DEG_TO_RAD));
    return true;
}
void O::Object::restart() noexcept
{
    sprite_.setPosition(coord_);
    sprite_.setRotation(180.f);
}

bool O::Object::is_free() const noexcept
{
    float cosin = cos(sprite_.getRotation() * CON::_DEG_TO_RAD);
    float sinus = sin(sprite_.getRotation() * CON::_DEG_TO_RAD);

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

bool O::Object::is_sand() const noexcept
{
    return map_->is_sand(sprite_.getPosition());
}
bool O::Object::is_accel() const noexcept
{
    return map_->is_accel(sprite_.getPosition());
}
bool O::Object::is_restart() const noexcept
{
    return map_->is_restart(sprite_.getPosition());
}

O::Tank::Tank(sf::View *view, M::Map *map, const sfC::ParamCar_t &cur_sort_tank, const std::string &file, const sf::IntRect &rect, const sf::Vector2f &coord, const sf::Color &color, float scale) noexcept
    : Object(map, file, rect, coord, color, scale),
      cur_sort_(cur_sort_tank),
      drifting_(0),
      speed_(0),
      motion_(),
      view_(view)
{
}
O::Tank::Tank(M::Map *map, const std::string &file, const sf::IntRect &rect, const sf::Vector2f &coord, const sf::Color &color, float scale) noexcept
    : Object(map, file, rect, coord, color, scale),
      cur_sort_(),
      drifting_(0),
      speed_(0),
      motion_(),
      view_(nullptr)
{
}

bool O::Tank::move_tank(const CharRect &movings, float time)
{
    switch (movings.Up)
    {
    case 1:
        motion_.Up = 1;
        speed_ += cur_sort_.GetDeceleration();
        break;
    case 0:
        if (motion_.Up == 1)
            speed_ += cur_sort_.GetAcceleration();
        break;
    case -1:
        motion_.Up = 0;
        break;
    }

    switch (movings.Down)
    {
    case 1:
        motion_.Down = 1;
        speed_ -= cur_sort_.GetBackCoef() * cur_sort_.GetAcceleration();
        break;
    case 0:
        if (motion_.Down == 1)
            speed_ -= cur_sort_.GetBackCoef() * cur_sort_.GetAcceleration();
        break;
    case -1:
        motion_.Down = 0;
        break;
    }

    if (motion_.Up == 0 && motion_.Down == 0)
        speed_ *= cur_sort_.GetDeceleration();

    if (speed_ > cur_sort_.GetMaxSpeed())
        speed_ = cur_sort_.GetMaxSpeed();
    if (speed_ < -1 * cur_sort_.GetBackCoef() * cur_sort_.GetMaxSpeed())
        speed_ = -1 * cur_sort_.GetBackCoef() * cur_sort_.GetMaxSpeed();

    //rotation
    switch (movings.Right)
    {
    case 1:
        motion_.Right = 1;
        drifting_ += cur_sort_.GetRotateSpeed();
        break;
    case 0:
        if (motion_.Right == 1)
        {
            drifting_ += cur_sort_.GetRotateSpeed();
        }
        break;
    case -1:
        motion_.Right = 0;
        break;
    }

    switch (movings.Left)
    {
    case 1:
        motion_.Left = 1;
        drifting_ -= cur_sort_.GetRotateSpeed();
        break;
    case 0:
        if (motion_.Left == 1)
            drifting_ -= cur_sort_.GetRotateSpeed();
        break;
    case -1:
        motion_.Left = 0;
        break;
    }

    if (motion_.Left == 0 && motion_.Right == 0)
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
        speed_ *= CON::SPEED_SAND;
    }
    else if (this->is_accel())
    {
        speed_ *= CON::SPEED_ACCEL;
    }
    else if (this->is_restart())
    {
        RestartTank(*this);
    }

    view_->setCenter(round(sprite_.getPosition().x), round(sprite_.getPosition().y));
    return true;
}

void O::Tank::stop_moving() noexcept
{
    drifting_ = 0.f;
    speed_ = 0.f;
}

void RestartTank(O::Tank &tank)
{
    tank.restart();
    tank.stop_moving();
}