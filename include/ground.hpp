#ifndef GROUND_HPP
#define GROUND_HPP
#include "SFML/Graphics/Sprite.hpp"

class Ground final : public sf::Sprite
{
    sf::Texture texture;

public:
    Ground(const WallID &type, const Material &material, const sf::Vector2f &position);
};

#endif
