#include "menu.h"
#include <iostream>
#include <string>
#include <algorithm>

using Utils::Difficulty;

Menu::Menu() : difficulty_level{ Difficulty::EASY } {}

void Menu::Run()
{
    bool loop{true};

    while (loop)
    {
        DisplayMenu();
        int choice = GetInput();
        if (IsInputValid(choice))
        {
            Difficulty level{DetermineDifficultyLevel(choice)};
            SetDifficultyLevel(level);
            loop = false;
        } else {
            std::cout << "Invalid Input" << std::endl;
        }
    }
}

bool Menu::IsInputValid(int option)
{
    return (option > 0) && (option < 5);
}

int Menu::GetInput()
{
    int choice;
    bool loop{true};
    std::string user_input;

    while (loop)
    {
        std::cout << "Difficulty: ";
        std::cin >> user_input;
        if (std::all_of(user_input.begin(), user_input.end(), isdigit))
        {
            choice = stoi(user_input);
            loop = false;
        } else {
            std::cout << "Invalid input. Please try again" << std::endl;
        }
    }
    return choice;
}

void Menu::DisplayMenu()
{
    std::cout << " ***** Welcome to the Snake Game *****\n\n"; 
    std::cout << "Main Menu\n";
    std::cout << "Select Your Level of Difficulty\n";
    std::cout << "1 - Easy\n";
    std::cout << "2 - Medium\n";
    std::cout << "3 - Hard\n";
    std::cout << "4 - Quit\n";
}

Difficulty Menu::DetermineDifficultyLevel(int level)
{
    switch (level)
    {
    case 2:
        return Difficulty::MEDIUM;
    case 3:
        return Difficulty::HARD;
    default:
        return Difficulty::EASY;
    }
}

Difficulty Menu::GetDifficultyLevel() const
{
    return difficulty_level;
}

void Menu::SetDifficultyLevel(Difficulty level)
{
    difficulty_level = level;
}