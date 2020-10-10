#ifndef MENU_H
#define MENU_H

#include "utils.h";

class Menu
{
public:
    Menu();
    void Run();
    Utils::Difficulty GetDifficultyLevel() const;

private:
    Utils::Difficulty difficulty_level;
    Utils::Difficulty DetermineDifficultyLevel(int level);
    int GetInput();
    bool IsInputValid(int);
    void DisplayMenu();
    void SetDifficultyLevel(Utils::Difficulty difficulty_level);
};

#endif
