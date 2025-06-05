#include "clumps/default_clump.hpp"

#include <player.hpp>

DefaultClump::DefaultClump(const sf::Vector2f& position)
    : Clump(position)
{
    rare_chances = {65, 80, 90, 96, 99};
    tex_chances = {65, 85, 95, 99};

    define_rare();
    define_tex();
}

func DefaultClump::try_destroy(const sf::Vector2i &click_pos, const std::shared_ptr<Player> &player) -> std::shared_ptr<ClumpItem>
{
    if (!clump.sprite.getGlobalBounds().contains(click_pos.x, click_pos.y)) return std::make_shared<ClumpItem>("It's not a clump!");

    const sf::Vector2f d = player->get_position() - clump.sprite.getPosition();
    const float range = std::sqrt(d.x * d.x + d.y * d.y);

    if (range > 40) return std::make_shared<ClumpItem>("Clump too far!");

    /* bonuses */
    float cost_mod = 1;

    const int random = -50 + std::rand() % 52 + player->get_bonus_value();
    if (random > 5 && rare != ClumpRare::LEGENDARY) rare = static_cast<ClumpRare>(rare + 1);
    if (random > 10) cost_mod += static_cast<float>(std::rand() % (random - 10)) / 10;

    return std::make_shared<ClumpItem>("OK", name, cost_mod, this->rare, this->texture_rare);
}