#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>

namespace Utilities
{
    enum class Difficulty
    {
        EASY,
        MEDIUM,
        HARD
    };

    std::size_t determine_frame_rate(Difficulty difficulty_level);
}

#endif