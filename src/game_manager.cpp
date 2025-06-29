#include "game_manager.hpp"

#include "scene_manager.hpp"
#include "scenes/main_menu_scene.hpp"

GameManager::GameManager() :
  window_(sf::RenderWindow(sf::VideoMode(800, 600), "Dungeon Archeology"))
{
  SceneManager::GetInstance().ChangeScene(std::make_unique<MainMenuScene>());
}

void GameManager::Run()
{
  while (window_.isOpen())
  {
    sf::Event event{};
    while (window_.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) window_.close();

      SceneManager::GetInstance().HandleEvent(event);
    }

    float delta_time = clock_.restart().asSeconds();
    SceneManager::GetInstance().Update(delta_time);

    window_.clear();
    SceneManager::GetInstance().Render(window_);
    window_.display();
  }
}

