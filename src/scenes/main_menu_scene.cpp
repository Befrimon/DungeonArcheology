#include "scenes/main_menu_scene.hpp"

#include "singletons/translation_manager.hpp"

#include <ranges>

#include "ui_parser.hpp"

MainMenuScene::MainMenuScene()
{
  /* Read data */
  toml::table data;
  try
  {
    data = toml::parse_file("assets/user_interface/main_menu.toml");
  } catch (const toml::parse_error& err)
  {
    std::stringstream text;
    text << "Error parsing TOML: " << err;
    SPDLOG_CRITICAL(text.str());
  }

  /* Init title */
  UIParser::applyConfig(*data["title"].as_table(), title_);
  UIParser::applyConfig(*data["start_button"].as_table(), start_button_);
  UIParser::applyConfig(*data["start_text"].as_table(), start_text_);

  SPDLOG_INFO("MainMenu scene initialized");
}

void MainMenuScene::handleEvent(const sf::Event &event) {}
void MainMenuScene::update(const float &delta) {}
void MainMenuScene::render(sf::RenderWindow &window)
{
  window.draw(title_);
  window.draw(start_button_);
  window.draw(start_text_);
}

void MainMenuScene::enter()
{
  SPDLOG_INFO("MainMenu scene entered");
}
void MainMenuScene::exit()
{
  SPDLOG_INFO("MainMenu scene exited");
}
