#ifndef UPDATER_HPP
#define UPDATER_HPP

#include "intercative.hpp"

class Updater final : public Interactive
{
    sf::Texture texture;

public:
    Updater();

    func interactive(const std::shared_ptr<UserInterface> &gm, const std::shared_ptr<Player> &player) const -> void override;
    func drawable() -> sf::Sprite override;
};

#endif
