#include "game_manager.hpp"

#include "singletons/scene_manager.hpp"
#include "singletons/resource_manager.hpp"
#include "singletons/translation_manager.hpp"
#include "scenes/main_menu_scene.hpp"

GameManager::GameManager() :
  window_(sf::RenderWindow(sf::VideoMode(800, 600), "Dungeon Archeology"))
{
  SPDLOG_INFO("Welcome to DungeonArcheology!");
  ResourceManager::getInstance();
  TranslationManager::getInstance();
  SceneManager::getInstance()->changeScene(std::make_unique<MainMenuScene>());
}

void GameManager::run()
{
  while (window_.isOpen())
  {
    sf::Event event{};
    while (window_.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        SceneManager::getInstance()->clearScenes();
        window_.close();
        SPDLOG_INFO("Goodbye!");
      }

      SceneManager::getInstance()->handleEvent(event);
    }

    float delta_time = clock_.restart().asSeconds();
    SceneManager::getInstance()->update(delta_time);

    window_.clear();
    SceneManager::getInstance()->render(window_);
    window_.display();
  }
}

