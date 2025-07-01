#ifndef UI_PARSER_HPP
#define UI_PARSER_HPP

class UIParser final
{
public:
  UIParser() = delete;
  static void applyConfig(const toml::table &config, sf::Text &object);
  static void applyConfig(const toml::table& config, sf::RectangleShape& object);
};

#endif
