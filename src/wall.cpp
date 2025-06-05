#include "wall.hpp"

const std::vector<sf::IntRect> wall_tile = {{},
    {{TILE*3, TILE*0}, TILE_SIZE}, {{TILE*1, TILE*2}, TILE_SIZE},       // top and bottom
    {{TILE*1, TILE*0}, TILE_SIZE}, {{TILE*3, TILE*2}, TILE_SIZE},       // left and right
    {{TILE*1, TILE*3}, TILE_SIZE}, {{TILE*0, TILE*0}, TILE_SIZE},       // top out corners
    {{TILE*0, TILE*2}, TILE_SIZE}, {{TILE*3, TILE*3}, TILE_SIZE},       // bottom out corners
    {{TILE*3, TILE*1}, TILE_SIZE}, {{TILE*2, TILE*2}, TILE_SIZE},       // top in corners
    {{TILE*2, TILE*0}, TILE_SIZE}, {{TILE*1, TILE*1}, TILE_SIZE},       // bottom in corners
    {{TILE*4, TILE*0}, TILE_SIZE}, {{TILE*13, TILE*1}, TILE_SIZE},
    {{TILE*13, TILE*0}, TILE_SIZE}, {{TILE*13, TILE*2}, TILE_SIZE}
};

Wall::Wall(const WallID &type, const Material &material, const sf::Vector2f &position)
{
    texture.loadFromFile("assets/SGQ_Dungeon/grounds_and_walls/walls.png");
    sprite.setTexture(texture);
    sf::IntRect current_wall = wall_tile[type];
    if (material == Material::STONE)
        current_wall.top += TILE*10;
    sprite.setTextureRect(current_wall);
    sprite.setOrigin(TILE / 2, TILE / 2);
    sprite.setPosition(position * SCALE.x);
    sprite.setScale(SCALE);
}

func Wall::bounds() const -> sf::FloatRect
{
    sf::FloatRect collision = sprite.getGlobalBounds();
    collision.left   += TILE * .5;
    collision.top    += TILE * .25;
    collision.width  -= TILE;
    collision.height -= TILE;
    return collision;
}


func Wall::checkCollision(const sf::FloatRect& playerBounds) const -> bool
{
    return bounds().intersects(playerBounds);
}

func Wall::resolveCollision(sf::Sprite& player) const -> void
{
    const sf::FloatRect player_bounds = player.getGlobalBounds();
    const sf::Vector2f player_pos(player.getPosition());

    float overlap_left = player_bounds.left + player_bounds.width - bounds().left;
    float overlap_right = bounds().left + bounds().width - player_bounds.left;
    float overlap_top = player_bounds.top + player_bounds.height - bounds().top;
    float overlap_bottom = bounds().top + bounds().height - player_bounds.top;

    const float min_overlap = std::min({overlap_left, overlap_right, overlap_top, overlap_bottom});
    if (min_overlap == overlap_left)
        player.setPosition(bounds().left - player_bounds.width / 2, player_pos.y);
    else if (min_overlap == overlap_right)
        player.setPosition(bounds().left + bounds().width + player_bounds.width / 2, player_pos.y);
    else if (min_overlap == overlap_top)
        player.setPosition(player_pos.x, bounds().top - player_bounds.height / 2);
    else if (min_overlap == overlap_bottom)
        player.setPosition(player_pos.x, bounds().top + bounds().height + player_bounds.height / 2);
}

func Wall::drawable() const -> sf::Sprite
{
    return sprite;
}
