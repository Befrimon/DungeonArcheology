#ifndef MAIN_MENU_SCENE_HPP
#define MAIN_MENU_SCENE_HPP

#include "scene.hpp"

class MainMenuScene final : public Scene
{
  sf::Text title_;
  sf::RectangleShape start_button_;
  sf::Text start_text_;
  sf::RectangleShape close_button_;
  sf::Text close_text_;

public:
  MainMenuScene();
  ~MainMenuScene() override = default;

  void HandleEvent(const sf::Event &event) override;
  void Update(const float &delta) override;
  void Render(sf::RenderWindow &window) override;
  void Enter() override;
  void Exit() override;
};

#endif
