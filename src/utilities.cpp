#include "utilities.h"

namespace Utilities
{
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