#include "resource_manager.hpp"

sf::Font ResourceManager::font_;

void ResourceManager::Initialize()
{
  font_.loadFromFile("assets/PixeloidFont/PixeloidSans.ttf");
  SPDLOG_INFO("Resources loaded");
}

sf::Font &ResourceManager::GetFont()
{
  return font_;
}
