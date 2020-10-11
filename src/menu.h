#ifndef MENU_H
#define MENU_H

#include "utilities.h"

class Menu
{
public:
    Menu();
    void Run();
    Utilities::Difficulty GetDifficultyLevel() const;

private:
    Utilities::Difficulty difficulty_level;
    Utilities::Difficulty DetermineDifficultyLevel(int level);
    int GetInput();
    bool IsInputValid(int);
    void DisplayMenu();
    void SetDifficultyLevel(Utilities::Difficulty difficulty_level);
};

#endif
