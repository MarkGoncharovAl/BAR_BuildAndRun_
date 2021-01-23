#include "random.hpp"

std::random_device Random::rd_;
std::mt19937 Random::gen_{Random::rd_()};

Random::Random(int init_start, int init_end) noexcept
    : dist_(init_start, init_end)
{
}

int Random::get() noexcept { return dist_(gen_); }
