#ifndef WALL_HPP
#define WALL_HPP

class Wall
{
    sf::Texture texture;
    sf::Sprite sprite;

    func bounds() const -> sf::FloatRect;

public:
    Wall(const WallID &type, const Material &material, const sf::Vector2f &position);

    func checkCollision(const sf::FloatRect& playerBounds) const -> bool;
    func resolveCollision(sf::Sprite& player) const -> void;
    func drawable() const -> sf::Sprite;
};

#endif