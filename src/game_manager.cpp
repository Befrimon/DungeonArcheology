#include "game_manager.hpp"

#include "scene_manager.hpp"
#include "resource_manager.hpp"
#include "translation_manager.hpp"
#include "scenes/main_menu_scene.hpp"

GameManager::GameManager() :
  window_(sf::RenderWindow(sf::VideoMode(800, 600), "Dungeon Archeology"))
{
  SPDLOG_INFO("Welcome to DungeonArcheology!");
  ResourceManager::Initialize();
  TranslationManager::Load("en");
  SceneManager::GetInstance().ChangeScene(std::make_unique<MainMenuScene>());
}

void GameManager::Run()
{
  while (window_.isOpen())
  {
    sf::Event event{};
    while (window_.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        SceneManager::GetInstance().ClearScenes();
        window_.close();
        SPDLOG_INFO("Goodbye!");
      }

      SceneManager::GetInstance().HandleEvent(event);
    }

    float delta_time = clock_.restart().asSeconds();
    SceneManager::GetInstance().Update(delta_time);

    window_.clear();
    SceneManager::GetInstance().Render(window_);
    window_.display();
  }
}

