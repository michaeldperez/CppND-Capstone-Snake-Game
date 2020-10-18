#include "scoreboard.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <functional>

const int MAX_STRING_SIZE = 25;

Entry::Entry(std::string name, int score)
    : name{ name }
    , score{ score } {}

Entry::Entry(Entry const& other)
    : name{ other.name }
    , score{ other.score } {}

Entry::Entry(Entry&& other) noexcept
    : name{ std::move(other.name) }
    , score{ std::exchange(other.score, 0) } {}

Entry& Entry::operator=(Entry const& other)
{
    if (this != &other)
    {
        name = other.name;
        score = other.score;
    }

    return *this;
}

Entry& Entry::operator=(Entry&& other) noexcept
{
    if (this != &other)
    {
        name = std::move(other.name);
        score = std::exchange(other.score, 0);
    }

    return *this;
}

bool Entry::operator>(Entry const& other) const
{
    return score > other.score;
}

Scoreboard::Scoreboard(std::string file_path)
    : scores_file_path{ file_path } { ReadScores(); }

Scoreboard::~Scoreboard() { SaveScores(); }

void Scoreboard::DisplayScores()
{
    std::cout << "\n";
    std::cout << "******** HIGH SCORES ********" << std::endl;
    std::cout << "Name                    Score" << std::endl;
    std::cout << "_____________________________" << std::endl;
    for (Entry& entry : scores)
    {
        std::string entry_name{ entry.name };
        int pad = MAX_STRING_SIZE - entry.name.size();
        std::cout << entry_name.append(pad, ' ') << entry.score << std::endl;
    }
    std::cout << "\n";
}

void Scoreboard::ReadScores()
{
    std::string line, name, score;
    std::ifstream stream{scores_file_path};
    if (stream.is_open())
    {
        while (std::getline(stream, line))
        {
            std::istringstream line_stream{line};
            line_stream >> name >> score;
            scores.emplace_back(name, std::stoi(score));
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
            stream << entry.name << " " << entry.score << std::endl;
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
    return new_score > scores.back().score;
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

void Scoreboard::HandleScore(int new_score)
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
        Entry entry{name, new_score};
        AddScore(entry);
        OrderScoreboard();
    }
    DisplayScores();
}