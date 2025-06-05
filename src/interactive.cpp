#include "intercative.hpp"

#include <player.hpp>
#include <user_interface.hpp>

func Interactive::interactive(const std::shared_ptr<UserInterface> &gui, const std::shared_ptr<Player> &player) const -> void
{
    if (!sprite.getGlobalBounds().intersects(player->get_bounds())) return;
    gui->set_mode(interface);
}
