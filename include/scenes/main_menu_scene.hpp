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

  void handleEvent(const sf::Event &event) override;
  void update(const float &delta) override;
  void render(sf::RenderWindow &window) override;
  void enter() override;
  void exit() override;
};

#endif
