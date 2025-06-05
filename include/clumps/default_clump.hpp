#ifndef DEFAULT_CLUMP_HPP
#define DEFAULT_CLUMP_HPP

#include <clump.hpp>

class DefaultClump final : public Clump
{
public:
    explicit DefaultClump(const sf::Vector2f &position);

    func try_destroy(const sf::Vector2i &click_pos, const std::shared_ptr<Player> &player) -> std::shared_ptr<ClumpItem>  override;
};

#endif
