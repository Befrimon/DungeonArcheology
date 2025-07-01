#include "../../include/singletons/resource_manager.hpp"

ResourceManager::ResourceManager()
{
  font_.loadFromFile("assets/pixeloid_font/PixeloidSans.ttf");
  SPDLOG_INFO("Resources loaded");
}

ResourceManager* ResourceManager::instance;
ResourceManager* ResourceManager::getInstance()
{
  if (instance == nullptr)
    instance = new ResourceManager();
  return instance;
}

sf::Font &ResourceManager::getFont()
{
  return font_;
}
