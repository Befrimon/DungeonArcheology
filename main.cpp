#include "game_manager.hpp"

int main()
{
  initLogging();
  GameManager main_game{};
  main_game.Run();
  return 0;
}