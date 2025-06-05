#include "player.hpp"

#include <wall.hpp>
#include <cmath>
#include <iostream>

Player::Player()
{
    frame_count = {3, 3, 4, 4};
    texture.loadFromFile("assets/SGQ_Dungeon/characters/main/elf.png");
    frame = sf::IntRect({0, 0}, TILE_SIZE);

    sprite.setTexture(texture);
    sprite.setTextureRect(frame);
    sprite.setOrigin(TILE / 2, TILE / 2);
    sprite.setScale(SCALE);

    /* pickaxe */
    weapon_texture.loadFromFile("assets/SGQ_Dungeon/weapons_and_projectiles/weapons_animated.png");
    attack_frame = sf::IntRect({0, WEAPON_TILE*12}, WEAPON_TILE_SIZE);

    weapon_sprite.setTexture(weapon_texture);
    weapon_sprite.setTextureRect(attack_frame);
    weapon_sprite.setOrigin(WEAPON_TILE / 2, WEAPON_TILE / 2);
    weapon_sprite.setScale(SCALE);
}

func Player::set_position(const sf::Vector2f &new_pos) -> void
{
    sprite.setPosition(new_pos * SCALE.x);
    weapon_sprite.setPosition(sprite.getPosition());
}
func Player::get_position() const -> sf::Vector2f
{
    return sprite.getPosition();
}
func Player::level_up() -> void
{
    if (current_level == max_level) return;
    current_level += 1;
}
func Player::get_level() const -> int
{
    return current_level;
}
func Player::get_level_cost() const -> int
{
    if (current_level == max_level) return 0;
    return pickaxe_upgrade[current_level].first;
}
func Player::get_bonus_value() const -> int
{
    return pickaxe_upgrade[current_level].second;
}

func Player::update(const float &delta) -> void
{
    sf::Vector2f movement(0.f, 0.f);
    float speed_scale = 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) speed_scale = 1.5f;

    if (is_attack) movement = {0.f, 0.f};

    if (movement.x != 0.f || movement.y != 0.f)
    {
        const float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement.x /= length;
        movement.y /= length;
    }
    sprite.setPosition(sprite.getPosition() + movement * speed * speed_scale * delta);
    weapon_sprite.setPosition(sprite.getPosition());

    /* animation */
    if (movement.x > 0 || cur_animation == IDLE_R) cur_animation = RUN_R;
    if (movement.x < 0 || cur_animation == IDLE_L) cur_animation = RUN_L;
    if (movement == sf::Vector2f{0.f, 0.f} && cur_animation == RUN_R) cur_animation = IDLE_R;
    if (movement == sf::Vector2f{0.f, 0.f} && cur_animation == RUN_L) cur_animation = IDLE_L;

    animation_time += delta;
    if (animation_time >= animation_speed)
    {
        animation_time = 0;
        frame.top = TILE * cur_animation;
        frame.left = (frame.left + TILE) % (frame_count[cur_animation] * TILE);
    }
    sprite.setTextureRect(frame);

    /* attack */
    if (is_attack) attack_anim_time += delta;
    if (attack_anim_time >= attack_anim_speed)
    {
        attack_anim_time = 0;
        attack_frame.left = (attack_frame.left + WEAPON_TILE) % (attack_frame_count * WEAPON_TILE);
        if (attack_frame.left == 0) is_attack = false;
    }
    weapon_sprite.setTextureRect(attack_frame);
}

func Player::click(const sf::Vector2i &position) -> void
{
    is_attack = true;
    const sf::Vector2f direction = static_cast<sf::Vector2f>(position) - sprite.getPosition();
    const float angle = std::atan2(direction.y, direction.x) * 180.0f / M_PI;
    if (angle <= -45 && angle > -135)
        attack_frame.top = WEAPON_TILE * 15;
    else if (angle <= 45 && angle > -45)
        attack_frame.top = WEAPON_TILE * 14;
    else if (angle <= 135 && angle > 45)
        attack_frame.top = WEAPON_TILE * 13;
    else
        attack_frame.top = WEAPON_TILE * 12;
}

func Player::check_bounds(const std::vector<std::shared_ptr<Wall>> &walls) -> void
{
    const sf::FloatRect playerBounds = sprite.getGlobalBounds();
    for (const auto& wall : walls)
        if (wall->checkCollision(playerBounds))
            wall->resolveCollision(sprite);
}

func Player::get_bounds() const -> sf::FloatRect
{
    return sprite.getGlobalBounds();
}


func Player::drawable() -> sf::Sprite
{
    combined_sprite.create(WIDTH, HEIGHT);
    combined_sprite.clear(sf::Color::Transparent);
    combined_sprite.draw(sprite);
    if (is_attack)
        combined_sprite.draw(weapon_sprite);
    combined_sprite.display();

    return sf::Sprite(combined_sprite.getTexture());
}