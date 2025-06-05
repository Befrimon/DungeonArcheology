#include "ground.hpp"

const std::vector<sf::IntRect> ground_tile = {{{TILE*9, TILE*2}, TILE_SIZE},
    {{TILE*10, TILE*0}, TILE_SIZE}, {{TILE*9, TILE*3}, TILE_SIZE},       // top and bottom
    {{TILE*8, TILE*1}, TILE_SIZE}, {{TILE*11, TILE*2}, TILE_SIZE},       // left and right
    {{TILE*8, TILE*0}, TILE_SIZE}, {{TILE*11, TILE*0}, TILE_SIZE},       // top out corners
    {{TILE*8, TILE*3}, TILE_SIZE}, {{TILE*11, TILE*3}, TILE_SIZE},       // bottom out corners
    {{TILE*6, TILE*2}, TILE_SIZE}, {{TILE*5, TILE*2}, TILE_SIZE},       // top in corners
    {{TILE*6, TILE*1}, TILE_SIZE}, {{TILE*5, TILE*1}, TILE_SIZE},       // bottom in corners
    {{TILE*12, TILE*1}, TILE_SIZE}, {},
    {{TILE*0, TILE*1}, TILE_SIZE}, {{TILE*2, TILE*3}, TILE_SIZE},
    {{TILE*9, TILE*0}, TILE_SIZE}, {{TILE*10, TILE*3}, TILE_SIZE},
    {{TILE*8, TILE*1}, TILE_SIZE}, {{TILE*11, TILE*1}, TILE_SIZE},
    {{TILE*4, TILE*1}, TILE_SIZE}, {{TILE*5, TILE*3}, TILE_SIZE},
    {{TILE*1, TILE*3}, TILE_SIZE},
};

Ground::Ground(const WallID &type, const Material &material, const sf::Vector2f &position)
{
    texture.loadFromFile("assets/SGQ_Dungeon/grounds_and_walls/grounds.png");

    setTexture(texture);
    sf::IntRect current_tile = ground_tile[type];
    if (material == Material::STONE)
        if (type == WallID::NONE && std::rand() % 100 < 40)
            current_tile = {{TILE*12, TILE*12}, TILE_SIZE};
        else if (type != WallID::NONE)
            current_tile.top += TILE*12;
    setTextureRect(current_tile);
    setOrigin(TILE / 2, TILE / 2);
    setPosition(position * SCALE.x);
    setScale(SCALE);
}
