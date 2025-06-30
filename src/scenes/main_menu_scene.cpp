#include "scenes/main_menu_scene.hpp"

#include "resource_manager.hpp"

MainMenuScene::MainMenuScene()
{
  title_.setFont(ResourceManager::GetFont());
  title_.setString("Dungeon Archeology");
  title_.setCharacterSize(48);
  title_.setFillColor(sf::Color::White);
  title_.setPosition(150, 60);

  SPDLOG_INFO("MainMenu scene initialized");
}

void MainMenuScene::HandleEvent(const sf::Event& event) {}
void MainMenuScene::Update(const float& delta) {}
void MainMenuScene::Render(sf::RenderWindow& window)
{
  window.draw(title_);
}

void MainMenuScene::Enter()
{
  SPDLOG_INFO("MainMenu scene entered");
}
void MainMenuScene::Exit()
{
  SPDLOG_INFO("MainMenu scene exited");
}
