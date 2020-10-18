#include "scoreboard.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <functional>

const int MAX_STRING_SIZE = 15;

Scoreboard::Entry::Entry(std::string name, int score, std::string difficulty)
    : name{ name }
    , score{ score }
    , difficulty{ difficulty } {}

Scoreboard::Entry::Entry(Entry const& other)
    : name{ other.name }
    , score{ other.score }
    , difficulty{ other.difficulty } {}

Scoreboard::Entry::Entry(Entry&& other) noexcept
    : name{ std::move(other.name) }
    , score{ std::exchange(other.score, 0) }
    , difficulty{ std::move(other.difficulty) } {}

Scoreboard::Entry& Scoreboard::Entry::operator=(Entry const& other)
{
    if (this != &other)
    {
        name = other.name;
        score = other.score;
        difficulty = other.difficulty;
    }

    return *this;
}

Scoreboard::Entry& Scoreboard::Entry::operator=(Entry&& other) noexcept
{
    if (this != &other)
    {
        name = std::move(other.name);
        score = std::exchange(other.score, 0);
        difficulty = std::move(other.difficulty);
    }

    return *this;
}

bool Scoreboard::Entry::operator>(Entry const& other) const
{
    return score > other.score;
}

std::string Scoreboard::Entry::GetName()
{
    return name;
}

std::string Scoreboard::Entry::GetDifficulty()
{
    return difficulty;
}

int Scoreboard::Entry::GetScore()
{
    return score;
}

Scoreboard::Scoreboard(std::string file_path)
    : scores_file_path{ file_path } { ReadScores(); }

Scoreboard::~Scoreboard() { SaveScores(); }

void Scoreboard::DisplayScores()
{
    std::cout << "\n";
    std::cout << "******     HIGH SCORES      ******" << std::endl;
    std::cout << "Name         Score      Difficulty" << std::endl;
    std::cout << "__________________________________" << std::endl;
    for (Entry& entry : scores)
    {
        std::string entry_name = entry.GetName();
        std::string entry_score = std::to_string(entry.GetScore());
        std::string entry_difficulty = entry.GetDifficulty();

        int name_pad = MAX_STRING_SIZE - entry_name.size();
        int score_pad = MAX_STRING_SIZE - entry_score.size();

        std::cout << entry_name.append(name_pad, ' ')
                  << entry_score.append(score_pad, ' ')
                  << entry_difficulty
                  << std::endl;
    }
    std::cout << "\n";
}

void Scoreboard::ReadScores()
{
    std::string line, name, score, difficulty;
    std::ifstream stream{scores_file_path};
    if (stream.is_open())
    {
        while (std::getline(stream, line))
        {
            std::istringstream line_stream{line};
            line_stream >> name >> score >> difficulty;
            scores.emplace_back(name, std::stoi(score), difficulty);
        }
        OrderScoreboard();
        stream.close();
    } else {
        std::ofstream new_file{scores_file_path};
    }
}

void Scoreboard::SaveScores()
{
    std::ofstream stream{scores_file_path, std::ios::trunc};
    if (stream.is_open())
    {
        for (Entry& entry : scores)
        {
            stream << entry.GetName()
                   << " "
                   << entry.GetScore()
                   << " "
                   << entry.GetDifficulty()
                   << std::endl;
        }
        stream.close();
    } else {
        std::cout << "Unable to write to " << scores_file_path << std::endl;
    }
}

bool Scoreboard::IsTopScore(int new_score)
{
    if (scores.size() < 10)
    {
        return true;
    }
    return new_score > scores.back().GetScore();
}

void Scoreboard::AddScore(Entry new_score)
{
    std::size_t number_of_high_scores{ scores.size() };

    if (number_of_high_scores < 10)
    {
        scores.push_back(new_score);
    } else {
        scores.at(number_of_high_scores) = new_score;
    }
}

void Scoreboard::OrderScoreboard()
{
    std::sort(
        scores.begin(),
        scores.end(), 
        std::greater<Entry>()
    );
}

void Scoreboard::HandleScore(int new_score, std::string difficulty)
{
    if (IsTopScore(new_score))
    {
        std::string name;
        std::cout << "Congratulations on the new high score!" << std::endl;
        std::cout << "Please enter your name: ";
        std::cin >> name;
        std::cout << "\n";
        if (name.size() > MAX_STRING_SIZE)
        {
            name = name.substr(0, MAX_STRING_SIZE);
        }
        Entry entry{name, new_score, difficulty};
        AddScore(entry);
        OrderScoreboard();
    }
    DisplayScores();
}