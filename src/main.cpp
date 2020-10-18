#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "menu.h"
#include "scoreboard.h"
#include "utilities.h"

int main() {

  Menu menu;
  menu.Run();

  Utilities::Difficulty difficulty_level = menu.GetDifficultyLevel();
  std::string kDifficulty = Utilities::DifficultyLevelString(difficulty_level);
  const auto [kInitialSpeed, kRateOfIncrease] = Utilities::DetermineSpeedConstants(difficulty_level);

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight, kDifficulty);
  Controller controller;
  Game game(kGridWidth, kGridHeight, kInitialSpeed, kRateOfIncrease);
  game.Run(controller, renderer, kMsPerFrame);
  
  Scoreboard scoreboard("high_scores.txt");
  int player_score = game.GetScore();
  scoreboard.HandleScore(player_score, kDifficulty);
  std::cout << "Game has terminated successfully!\n";

  return 0;
}