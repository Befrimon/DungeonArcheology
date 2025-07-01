#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

class GameManager final
{
  sf::RenderWindow window_;
  sf::Clock clock_;

public:
  GameManager();

  void run();
};

#endif
