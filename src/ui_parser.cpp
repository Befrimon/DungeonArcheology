#include "ui_parser.hpp"

#include "singletons/translation_manager.hpp"
#include "singletons/resource_manager.hpp"

void UIParser::applyConfig(const toml::table& config, sf::Text &object)
{
  object.setFont(ResourceManager::getInstance()->getFont(config["font_key"].value_or("default")));
  object.setString(TranslationManager::getInstance()->get(config["text_key"].value_or("")));
  object.setCharacterSize(config["char_size"].value_or(10));
  object.setFillColor(sf::Color(
    config["fill_color"]["r"].value_or(0),
    config["fill_color"]["g"].value_or(0),
    config["fill_color"]["b"].value_or(0)));
  const sf::FloatRect bounds = object.getGlobalBounds();
  object.setOrigin(static_cast<sf::Vector2f>(sf::Vector2i(
    static_cast<int>(bounds.width / 2),
    static_cast<int>(bounds.height / 2))));
  object.setPosition(sf::Vector2f(config["position"]["x"].value_or(0.f), config["position"]["y"].value_or(0.f)));
  object.setScale(config["scale"]["x"].value_or(1), config["scale"]["y"].value_or(1));
}

void UIParser::applyConfig(const toml::table& config, sf::RectangleShape &object)
{
  object.setFillColor(sf::Color(
    config["fill_color"]["r"].value_or(0),
    config["fill_color"]["g"].value_or(0),
    config["fill_color"]["b"].value_or(0)));
  object.setSize(sf::Vector2f(config["size"]["x"].value_or(0.f), config["size"]["y"].value_or(0.f)));
  const sf::FloatRect bounds = object.getGlobalBounds();
  object.setOrigin(static_cast<sf::Vector2f>(sf::Vector2i(
    static_cast<int>(bounds.width / 2),
    static_cast<int>(bounds.height / 2))));
  object.setPosition(sf::Vector2f(config["position"]["x"].value_or(0.f), config["position"]["y"].value_or(0.f)));
  object.setScale(config["scale"]["x"].value_or(1), config["scale"]["y"].value_or(1));
}

void UIParser::applyConfig(const toml::table &config, sf::Sprite &object)
{
  object = sf::Sprite(ResourceManager::getInstance()->getTexture(config["texture_key"].value_or("")));
  const sf::FloatRect bounds = object.getGlobalBounds();
  object.setOrigin(static_cast<sf::Vector2f>(sf::Vector2i(
    static_cast<int>(bounds.width / 2),
    static_cast<int>(bounds.height / 2))));
  object.setPosition(sf::Vector2f(config["position"]["x"].value_or(0.f), config["position"]["y"].value_or(0.f)));
  object.setScale(config["scale"]["x"].value_or(1), config["scale"]["y"].value_or(1));
}
void UIParser::applyConfig(const toml::table &config, SliceSprite &object)
{
  object.setTexture(
    ResourceManager::getInstance()->getTexture(config["texture_key"].value_or("")),
    sf::Vector2u(config["tile_size"]["x"].value_or(0), config["tile_size"]["y"].value_or(0)));
  object.setSize(sf::Vector2f(config["size"]["x"].value_or(0), config["size"]["y"].value_or(0)));
  const sf::FloatRect bounds = object.getGlobalBounds();
  object.setOrigin(static_cast<sf::Vector2f>(sf::Vector2i(
    static_cast<int>(bounds.width / 2),
    static_cast<int>(bounds.height / 2))));
  object.setPosition(sf::Vector2f(config["position"]["x"].value_or(0.f), config["position"]["y"].value_or(0.f)));
  object.setScale(config["scale"]["x"].value_or(1), config["scale"]["y"].value_or(1));
}