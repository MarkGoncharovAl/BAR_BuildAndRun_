#include <iostream>

struct A
{
    constexpr A(int x) : x_{x} {}
    constexpr int get_x() const { return x_; }

    int x_ = 0;
};

constexpr A var{5};