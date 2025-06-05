#include "clump.hpp"

#include <player.hpp>

std::vector<sf::Vector2i> frames = {
    {TILE*0, TILE*4}, {TILE*2, TILE*4}, {TILE*1, TILE*4}, {TILE*3, TILE*4}, {TILE*0, TILE*5}
};

func Clump::define_rare() -> void
{
    const int random = std::rand() % 100;
    if (random < rare_chances[0]) rare = ClumpRare::NOTHING;
    else if (random < rare_chances[1]) rare = ClumpRare::COMMON;
    else if (random < rare_chances[2]) rare = ClumpRare::UNCOMMON;
    else if (random < rare_chances[3]) rare = ClumpRare::RARE;
    else if (random < rare_chances[4]) rare = ClumpRare::EPIC;
    else rare = ClumpRare::LEGENDARY;
}
func Clump::define_tex() -> void
{
    const int random = std::rand() % 100;
    if (random < tex_chances[0]) texture_rare = ClumpRare::COMMON;
    else if (random < tex_chances[1]) texture_rare = ClumpRare::UNCOMMON;
    else if (random < tex_chances[2]) texture_rare = ClumpRare::RARE;
    else if (random < tex_chances[3]) texture_rare = ClumpRare::EPIC;
    else texture_rare = ClumpRare::LEGENDARY;
    clump.sprite.setTextureRect(sf::IntRect(frames[texture_rare-1], TILE_SIZE));
}

Clump::Clump(const sf::Vector2f &position)
{
    const int random = 4 + std::rand() % 9;
    for (int i = 0; i < random; i++)
        name += static_cast<char>(65 + std::rand() % 26);

    clump.texture.loadFromFile("assets/SGQ_Dungeon/props/props.png");
    clump.sprite.setTexture(clump.texture);
    clump.sprite.setOrigin(TILE / 2, TILE / 2);
    clump.sprite.setPosition(position * SCALE.x);
    clump.sprite.setScale(SCALE);

    define_rare();
    define_tex();
}

func Clump::drawable() const -> sf::Sprite
{
    return clump.sprite;
}
