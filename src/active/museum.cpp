#include "../../include/active/museum.hpp"

Museum::Museum()
{
    texture.loadFromFile("assets/SGQ_Dungeon/props/minecart_and_rails.png");

    for (int i = 0; i < 3; i++)
    {
        sf::Sprite wl;
        wl.setTexture(texture);
        wl.setTextureRect({{i*TILE, 6*TILE}, TILE_SIZE});
        wl.setScale(SCALE);
        wl.setPosition(i*TILE*SCALE.x, 4*TILE*SCALE.y);
        sprites.push_back(wl);
    }
    const std::vector<sf::Vector2i> tile = {{0, 0}, {2, 0}, {1, 1}, {2, 1}, {2, 1}, {3, 0}};
    const std::vector<sf::Vector2f> coord = {{1, 3}, {2, 3}, {3, 3}, {3, 2}, {3, 1}, {3, 0}};
    for (int i = 0; i < 6; i++)
    {
        sf::Sprite wl;
        wl.setTexture(texture);
        wl.setTextureRect({tile[i]*TILE, TILE_SIZE});
        wl.setScale(SCALE);
        wl.setPosition(coord[i]*TILE_F*SCALE.x);
        sprites.push_back(wl);
    }
    sf::Sprite cart1;
    cart1.setTexture(texture);
    cart1.setTextureRect({sf::Vector2i{2, 4}*TILE, TILE_SIZE});
    cart1.setScale(SCALE);
    cart1.setPosition(sf::Vector2f{2.75, 2.75}*TILE_F*SCALE.x);
    sprites.push_back(cart1);
    sf::Sprite cart2;
    cart2.setTexture(texture);
    cart2.setTextureRect({sf::Vector2i{1, 4}*TILE, TILE_SIZE});
    cart2.setScale(SCALE);
    cart2.setPosition(sf::Vector2f{3, 1}*TILE_F*SCALE.x);
    sprites.push_back(cart2);

    interface = UIMode::MUSEUM;
}

func Museum::drawable() -> sf::Sprite
{
    rails.create(4*TILE*SCALE.x, 5*TILE*SCALE.y);
    rails.clear(sf::Color::Transparent);

    for (auto sprite : sprites)
        rails.draw(sprite);

    rails.display();
    sprite = sf::Sprite(rails.getTexture());
    sprite.setPosition(sf::Vector2f{11.5, 6.5}*TILE_F*SCALE.x);
    return sprite;
}

