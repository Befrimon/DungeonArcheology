#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

class GameManager;

class UserInterface
{
    sf::RenderTexture combined_texture;
    GameManager* parent;
    sf::Font font;

    float click_cd = 0.f;
    float click_cd_speed = .2f;

    /* Base UI */
    sf::Sprite coin_icon;
    sf::Text coin_label;
    sf::Sprite crystal_icon;
    sf::Text crystal_label;

    RenderObject menu_brick;
    RenderObject title_brick;
    sf::Text title_label;

    /* Upgrader */
    RenderObject upgrader_coins;
    RenderObject pickaxe_level;
    sf::Sprite up_coins_icon;
    sf::Text up_coins_label;
    sf::Sprite pickaxe_icon;
    sf::Text pickaxe_label;

    RenderObject pickaxe_field;
    sf::Sprite pickaxe_anim;
    int pickaxe_frame_count = 5;
    sf::IntRect pickaxe_frame{{0, WEAPON_TILE*12}, WEAPON_TILE_SIZE};
    float pickaxe_anim_speed = .2f;
    float pickaxe_anim_time = 0.f;
    sf::Text pickaxe_title;
    sf::Text pickaxe_description;
    RenderObject pickaxe_button;
    sf::Text pickaxe_cost;

    RenderObject dungeon_field;
    sf::Sprite dungeon_anim;
    int dungeon_frame_count = 3;
    sf::IntRect dungeon_frame{{}, TILE_SIZE};
    float dungeon_anim_speed = .4f;
    float dungeon_anim_time = 0.f;
    sf::Text dungeon_title;
    sf::Text dungeon_description;
    RenderObject dungeon_button;
    sf::Text dungeon_cost;

    sf::Text empty;
    sf::Sprite crystal_museum_icon;
    RenderObject crystal_view;
    RenderObject button_left;
    sf::Text left_label;
    RenderObject button_right;
    sf::Text right_label;
    RenderObject crystal_image;
    sf::Text crystal_title;
    sf::Text crystal_description;
    RenderObject sell_button;
    sf::Text sell;
    RenderObject sold_label;
    sf::Text sold;
    int current_crystal = 0;

    UIMode mode = UIMode::BASE;
    func base_ui() -> void;
    func settings() -> void;
    func upgrader() -> void;
    func museum() -> void;

    friend func pieces_to_rect(const sf::Texture &tex, const sf::Vector2i &coord, const sf::Vector2i &size, RenderObject &render) -> void;

public:
    explicit UserInterface(GameManager *parent);

    // func scroll_museum(const int &direction) -> void;
    func click(const sf::Vector2i &click_pos) -> void;
    func update_anims(const float &delta) -> void;
    func drawable() -> sf::Sprite;

    func call_rebuild() const -> void;
    func set_mode(const UIMode &new_mode) -> void;
    func get_mode() const -> UIMode;
};

#endif
