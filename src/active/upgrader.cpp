#include "active/upgrader.hpp"

Upgrader::Upgrader()
    :Interactive()
{
    texture.loadFromFile("assets/SGQ_Dungeon/props/props.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({TILE*12, 0}, TILE_SIZE*2));
    sprite.setScale(SCALE);
    sprite.setPosition({TILE*15, TILE*4.5});

    interface = UIMode::UPGRADER;
}

func Upgrader::drawable() -> sf::Sprite
{
    return sprite;
}