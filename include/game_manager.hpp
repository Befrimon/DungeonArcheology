#ifndef GAME_HPP
#define GAME_HPP

class Player;
class UserInterface;
class Interactive;
class Wall;
class Ground;
struct ClumpItem;
class Clump;

class GameManager
{
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Event event{};

    int coins = 110;
    int rebuild_cost = 10;

    std::shared_ptr<Player> player;
    std::shared_ptr<UserInterface> gui;

    /* sprites */
    std::vector<std::shared_ptr<Interactive>> actions;

    /* landscape */
    std::vector<std::shared_ptr<Wall>> walls;
    std::vector<std::shared_ptr<Ground>> grounds;
    std::vector<std::shared_ptr<Clump>> clumps;

    /* Remove clump */
    std::vector<std::shared_ptr<ClumpItem>> inventory;
    int rm_target;
    float rm_countdown = -1;

public:
    GameManager();

    func generate_cave() -> void;
    func get_coins() const -> int;
    func remove_coins(const int &count) -> void;
    func add_coins(const int &count) -> void;
    func get_player() const ->  std::shared_ptr<Player>;
    func get_crystal_count() const -> int;
    func get_crystals() const -> std::vector<std::shared_ptr<ClumpItem>>;
    func sell_crystal(const int &index) -> void;
    func rare_to_cost(const ClumpRare &rare, const ClumpRare &tex_rare, const float &mod) -> int;
};

#endif
