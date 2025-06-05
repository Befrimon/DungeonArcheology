#include "active/updater.hpp"

#include <user_interface.hpp>
#include <player.hpp>

Updater::Updater()
    :Interactive()
{
    texture.loadFromFile("assets/SGQ_Dungeon/props/props.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({TILE*14, 0}, TILE_SIZE*2));
    sprite.setScale(SCALE);
    sprite.setPosition({TILE*7*SCALE.x, TILE*10.5f*SCALE.y});
    sprite.setRotation(-90);
}

func Updater::interactive(const std::shared_ptr<UserInterface> &gui, const std::shared_ptr<Player> &player) const -> void
{
    if (!sprite.getGlobalBounds().intersects(player->get_bounds())) return;
    gui->call_rebuild();
}

func Updater::drawable() -> sf::Sprite
{
    return sprite;
}
