#ifndef UTILS_H
#define UTILS_H
#include <iostream>

namespace Utils
{
    enum class Difficulty
    {
        EASY,
        MEDIUM,
        HARD
    };

    std::size_t determine_frame_rate(Difficulty difficulty_level)
    {
        switch (difficulty_level)
        {
        case Difficulty::MEDIUM:
            return 65;
        case Difficulty::HARD:
            return 70;
        default:
            return 60;
        }
    }
}

#endif