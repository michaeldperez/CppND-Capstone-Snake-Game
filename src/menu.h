#ifndef MENU_H
#define MENU_H

enum class Difficulty
{
    EASY,
    MEDIUM,
    HARD
};

class Menu
{
public:
    Menu();
    void Run();
    Difficulty GetDifficultyLevel() const;

private:
    Difficulty difficulty_level;
    Difficulty DetermineDifficultyLevel(int level);
    int GetInput();
    bool IsInputValid(int);
    void DisplayMenu();
    void SetDifficultyLevel(Difficulty difficulty_level);
};

#endif
