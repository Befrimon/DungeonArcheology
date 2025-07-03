#ifndef UI_PARSER_HPP
#define UI_PARSER_HPP

#include "slice_sprite.hpp"

class UIParser final
{
public:
  UIParser() = delete;
  static void applyConfig(const toml::table &config, sf::Text &object);
  static void applyConfig(const toml::table& config, sf::RectangleShape &object);
  static void applyConfig(const toml::table& config, sf::Sprite &object);
  static void applyConfig(const toml::table& config, SliceSprite &object);
};

#endif
