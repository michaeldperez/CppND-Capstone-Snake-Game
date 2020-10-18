#include <unordered_map>
#include "utilities.h"

namespace Utilities
{
    namespace {
        const std::unordered_map<Difficulty, std::string> difficulty_map = {
            { Difficulty::EASY, "Easy" },
            { Difficulty::MEDIUM, "Medium" },
            { Difficulty::HARD, "Hard" }
        };
    }

    SpeedConstants DetermineSpeedConstants(Difficulty difficulty_level)
    {
        switch (difficulty_level)
        {
        case Difficulty::MEDIUM:
            return SpeedConstants{ 0.2f, 0.04f };
        case Difficulty::HARD:
            return SpeedConstants{ 0.4f, 0.08f };
        default:
            return SpeedConstants{ 0.1f, 0.02f };
        }
    }

    std::string DifficultyLevelString(Difficulty difficulty_level)
    {
        return difficulty_map.at(difficulty_level);
    }
}