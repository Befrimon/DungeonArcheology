#include "../../include/singletons/resource_manager.hpp"

ResourceManager::ResourceManager()
{
  /* Load fonts */
  fonts_["default"].loadFromFile("assets/pixeloid_font/PixeloidSans.ttf");

  /* Load textures */
  textures_["ui_elements"].loadFromFile("assets/textures/game_ui/ui_elements.png");
  textures_["ui_elements::button_1"].loadFromImage(textures_["ui_elements"].copyToImage(), sf::IntRect(0, 160, 24, 24));

  SPDLOG_INFO("Resources loaded");
}

ResourceManager* ResourceManager::instance;
ResourceManager* ResourceManager::getInstance()
{
  if (instance == nullptr)
    instance = new ResourceManager();
  return instance;
}

sf::Font &ResourceManager::getFont(const std::string &key)
{
  return fonts_[key];
}

sf::Texture &ResourceManager::getTexture(const std::string &key)
{
  return textures_[key];
}
