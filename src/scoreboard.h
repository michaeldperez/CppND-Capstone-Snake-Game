#include <string>
#include <vector>
class Entry
{
public:
    Entry(std::string name, int score, std::string difficulty);
    Entry(Entry const& other);
    Entry(Entry&& other) noexcept;
    ~Entry()=default;

    Entry& operator=(Entry const& other);
    Entry& operator=(Entry&& other) noexcept; 
    bool operator>(Entry const& other) const;

    std::string GetName();
    std::string GetDifficulty();
    int GetScore();

private:
    std::string name;
    std::string difficulty;
    int score;
};

class Scoreboard
{
public:
    Scoreboard(std::string file_path);
    ~Scoreboard();
    void HandleScore(int new_score, std::string difficulty);
private:
    std::string scores_file_path;
    std::vector<Entry> scores;
    void DisplayScores();
    bool IsTopScore(int new_score);
    void ReadScores();
    void SaveScores();
    void AddScore(Entry new_score);
    void OrderScoreboard();
};
