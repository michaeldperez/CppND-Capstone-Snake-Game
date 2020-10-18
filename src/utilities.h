#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
#include <string>

namespace Utilities
{
    enum class Difficulty
    {
        EASY,
        MEDIUM,
        HARD
    };

    struct SpeedConstants
    {
        float initial_speed;
        float rate_of_increase;
    };

    SpeedConstants DetermineSpeedConstants(Difficulty difficulty_level);
    std::string DifficultyLevelString(Difficulty difficulty_level);
}

#endif