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
  UIParser::applyConfig(*data["huh_button"].as_table(), huh_button_);
  UIParser::applyConfig(*data["huh_text"].as_table(), huh_text_);
  UIParser::applyConfig(*data["close_button"].as_table(), close_button_);
  UIParser::applyConfig(*data["close_text"].as_table(), close_text_);

  SPDLOG_INFO("MainMenu scene initialized");
}

void MainMenuScene::handleEvent(const sf::Event &event)
{
  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
  {
    if (start_button_.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
      SPDLOG_INFO("START!!!");
    if (start_button_.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
      SPDLOG_INFO("HUH!!!");
    if (start_button_.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
      SPDLOG_INFO("CLOSE!!!");
  }
}
void MainMenuScene::update(const float &delta) {}
void MainMenuScene::render(sf::RenderWindow &window)
{
  window.draw(title_);
  window.draw(start_button_);
  window.draw(start_text_);
  window.draw(huh_button_);
  window.draw(huh_text_);
  window.draw(close_button_);
  window.draw(close_text_);
}

void MainMenuScene::enter()
{
  SPDLOG_INFO("MainMenu scene entered");
}
void MainMenuScene::exit()
{
  SPDLOG_INFO("MainMenu scene exited");
}
