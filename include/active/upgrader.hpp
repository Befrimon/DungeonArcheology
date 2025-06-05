#ifndef UPGRADER_HPP
#define UPGRADER_HPP

#include "intercative.hpp"

class Upgrader final : public Interactive
{
    sf::Texture texture;

public:
    Upgrader();
    func drawable() -> sf::Sprite override;
};

#endif
