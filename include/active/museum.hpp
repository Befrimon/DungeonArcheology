#ifndef MUSEUM_HPP
#define MUSEUM_HPP
#include "intercative.hpp"

class UserInterface;
class Player;

class Museum final : public Interactive
{
    sf::RenderTexture rails;
    sf::Texture texture;

    std::vector<sf::Sprite> sprites;

public:
    Museum();
    func drawable() -> sf::Sprite override;
};

#endif
