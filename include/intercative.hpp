#ifndef INTERCATIVE_HPP
#define INTERCATIVE_HPP

class Player;
class UserInterface;

class Interactive
{
protected:
    UIMode interface = UIMode::BASE;
    sf::Sprite sprite;

public:
    Interactive() = default;
    virtual ~Interactive() = default;

    virtual func interactive(const std::shared_ptr<UserInterface> &gui, const std::shared_ptr<Player> &player) const -> void;
    virtual func drawable() -> sf::Sprite = 0;
};

#endif
