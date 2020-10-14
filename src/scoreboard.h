#include <string>
#include <vector>
struct Entry
{
    Entry(std::string name, int score);
    Entry(Entry const& other);
    Entry(Entry&& other) noexcept;
    ~Entry()=default;
    Entry& operator=(Entry const& other);
    Entry& operator=(Entry&& other) noexcept; 
    bool operator>(Entry const& other) const;
    std::string name;
    int score;
};

class Scoreboard
{
public:
    Scoreboard(std::string file_path);
    ~Scoreboard();
    void HandleScore(int new_score);
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
