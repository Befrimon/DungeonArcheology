#ifndef PLAYER_HPP
#define PLAYER_HPP

class Wall;
class Player
{
    sf::RenderTexture combined_sprite;
    float speed = 200.f;

    /* Character animation */
    enum Anim {IDLE_R, IDLE_L, RUN_R, RUN_L, MAX};
    Anim cur_animation = IDLE_R;
    sf::Texture texture;
    sf::Sprite sprite;

    std::vector<int> frame_count;
    sf::IntRect frame;
    float animation_speed = .2f;
    float animation_time = 0.f;

    /* pickaxe animation */
    sf::Texture weapon_texture;
    sf::Sprite weapon_sprite;
    bool is_attack = false;
    std::vector<std::pair<int, int>> pickaxe_upgrade = {{500, 2}, {800, 5}, {1200, 8}, {2100, 13}, {3400, 15}, {6900, 18}};
    int max_level = 5;
    int current_level = 0;

    int attack_frame_count = 5;
    sf::IntRect attack_frame;
    float attack_anim_speed = .2f;
    float attack_anim_time = 0.f;


public:
    Player();

    func set_position(const sf::Vector2f &new_pos) -> void;
    func get_position() const -> sf::Vector2f;
    func level_up() -> void;
    func get_level() const -> int;
    func get_level_cost() const -> int;
    func get_bonus_value() const -> int;

    func update(const float &delta) -> void;
    func click(const sf::Vector2i &position) -> void;
    func check_bounds(const std::vector<std::shared_ptr<Wall>> &walls) -> void;
    func get_bounds() const -> sf::FloatRect;

    func drawable() -> sf::Sprite;
};

#endif
