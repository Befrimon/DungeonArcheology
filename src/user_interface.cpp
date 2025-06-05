#include "user_interface.hpp"

#include <iostream>

#include "clump.hpp"
#include "game_manager.hpp"
#include "player.hpp"


auto hud = sf::Texture();
auto ui_elem = sf::Texture();
auto props = sf::Texture();
auto anim_props = sf::Texture();
auto weapons = sf::Texture();
std::vector<std::string> rare_str = {"", "common", "uncommon", "rare", "epic", "legendary"};

func pieces_to_rect(const sf::Texture& tex, const sf::Vector2i& coord, const sf::Vector2i& size, RenderObject& render) -> void
{
    sf::RenderTexture result;
    result.create(size.y * UI_TILE * SCALE.y, size.x * UI_TILE * SCALE.x);
    result.clear(sf::Color::Transparent);

    std::vector<sf::Vector2i> tiles;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
        tiles.push_back({i, j});

    for (int x = 0; x < size.x; x++) for (int y = 0; y < size.y; y++)
    {
        sf::Sprite tile;
        tile.setTexture(tex);
        tile.setScale(SCALE);
        sf::Vector2i tile_coord;
        if (x == 0 && y == 0) tile_coord = tiles[0];
        else if (x != 0 && x != size.x-1 && y == 0) tile_coord = tiles[1];
        else if (x == size.x-1 && y == 0) tile_coord = tiles[2];
        else if (x == 0 && y != 0 && y != size.y-1) tile_coord = tiles[3];
        else if (x == size.x-1 && y != 0 && y != size.y-1) tile_coord = tiles[5];
        else if (x == 0 && y == size.y-1) tile_coord = tiles[6];
        else if (x != 0 && x != size.x-1 && y == size.y-1) tile_coord = tiles[7];
        else if (x == size.x-1 && y == size.y-1) tile_coord = tiles[8];
        else tile_coord = tiles[4];
        tile.setTextureRect(sf::IntRect((coord + tile_coord) * UI_TILE, UI_TILE_SIZE));
        tile.setPosition(sf::Vector2f{y * UI_TILE_F, x * UI_TILE_F} * SCALE.x);
        result.draw(tile);
    }
    result.display();
    render.texture = result.getTexture();
    render.sprite.setTexture(render.texture);
}

UserInterface::UserInterface(GameManager *parent)
    : parent(parent)
{
    font.loadFromFile("assets/Pixeloid_Font_0_5/TrueType/PixeloidSans.ttf");

    hud.loadFromFile("assets/SGQ_ui/game_ui/hud.png");
    ui_elem.loadFromFile("assets/SGQ_ui/game_ui/ui_elements.png");
    props.loadFromFile("assets/SGQ_Dungeon/props/props.png");
    anim_props.loadFromFile("assets/SGQ_Dungeon/props/animated_props.png");
    weapons.loadFromFile("assets/SGQ_Dungeon/weapons_and_projectiles/weapons_animated.png");

    /*=-= |BASE UI| =-=*/
    coin_icon.setTexture(hud);
    coin_icon.setTextureRect({{0, TILE}, TILE_SIZE});
    coin_icon.setPosition({TILE, TILE * 3});
    coin_icon.setScale(SCALE * 1.5f);

    coin_label.setFont(font);
    coin_label.setCharacterSize(28);
    coin_label.setFillColor(sf::Color(212, 210, 155));
    coin_label.setPosition({TILE * 4, TILE * 3.5});

    crystal_icon.setTexture(hud);
    crystal_icon.setTextureRect({{TILE, TILE}, TILE_SIZE});
    crystal_icon.setPosition({TILE, TILE * 6});
    crystal_icon.setScale(SCALE * 1.5f);

    crystal_label.setFont(font);
    crystal_label.setCharacterSize(28);
    crystal_label.setFillColor(sf::Color(212, 210, 155));
    crystal_label.setPosition({TILE * 4, TILE * 6.5});

    /*=-= |BRICK MENU| =-=*/
    pieces_to_rect(ui_elem, {0, 0}, {35, 50}, menu_brick);
    menu_brick.sprite.setPosition((WIDTH - UI_TILE*50*SCALE.x)/2, (HEIGHT - UI_TILE*35*SCALE.y)/2);
    const sf::FloatRect mbr_bounce = menu_brick.sprite.getGlobalBounds();

    title_label.setFont(font);
    title_label.setCharacterSize(28);
    title_label.setFillColor(sf::Color(212, 210, 155));
    title_label.setPosition(WIDTH/2-title_label.getGlobalBounds().getSize().x/2, mbr_bounce.top - UI_TILE * SCALE.y);

    pieces_to_rect(ui_elem, {0, 5}, {3, 12}, title_brick);
    title_brick.sprite.setPosition((WIDTH - UI_TILE*12*SCALE.x)/2, mbr_bounce.top-UI_TILE*1.5*SCALE.x);

    /*=-= |UPGRADER| =-=*/
    pieces_to_rect(ui_elem, {8, 3}, {4, 18}, upgrader_coins);
    pieces_to_rect(ui_elem, {8, 3}, {4, 18}, pickaxe_level);
    upgrader_coins.sprite.setPosition(mbr_bounce.left + 4*UI_TILE, mbr_bounce.top + 2*UI_TILE);
    pickaxe_level.sprite.setPosition(
        mbr_bounce.left + mbr_bounce.width - UI_TILE*18*SCALE.x - UI_TILE*4,
        mbr_bounce.top + 2*UI_TILE
    );

    up_coins_icon.setTexture(hud);
    up_coins_icon.setTextureRect({{0, TILE}, TILE_SIZE});
    up_coins_icon.setPosition(
        upgrader_coins.sprite.getGlobalBounds().left + 2*UI_TILE,
        upgrader_coins.sprite.getGlobalBounds().top + UI_TILE
    );
    up_coins_icon.setScale(SCALE * 1.5f);

    up_coins_label.setFont(font);
    up_coins_label.setCharacterSize(28);
    up_coins_label.setFillColor(sf::Color(212, 210, 155));
    up_coins_label.setPosition(
        upgrader_coins.sprite.getGlobalBounds().left + 9*UI_TILE,
        upgrader_coins.sprite.getGlobalBounds().top + 1.6*UI_TILE
    );

    pickaxe_icon.setTexture(props);
    pickaxe_icon.setTextureRect({{TILE*2, TILE*5}, TILE_SIZE});
    pickaxe_icon.setPosition(
        pickaxe_level.sprite.getGlobalBounds().left + 2*UI_TILE,
        pickaxe_level.sprite.getGlobalBounds().top + UI_TILE
    );
    pickaxe_icon.setScale(SCALE * 1.5f);

    pickaxe_label.setFont(font);
    pickaxe_label.setCharacterSize(28);
    pickaxe_label.setFillColor(sf::Color(212, 210, 155));
    pickaxe_label.setPosition(
        pickaxe_level.sprite.getGlobalBounds().left + 9*UI_TILE,
        pickaxe_level.sprite.getGlobalBounds().top + 1.6*UI_TILE
    );

    pieces_to_rect(ui_elem, {0, 32}, {10, 48}, pickaxe_field);
    pickaxe_field.sprite.setPosition(mbr_bounce.left + UI_TILE*SCALE.x, mbr_bounce.top + 6*UI_TILE*SCALE.x);
    pickaxe_anim.setTexture(weapons);
    pickaxe_anim.setScale(SCALE*3.f);
    pickaxe_anim.setPosition(
        pickaxe_field.sprite.getGlobalBounds().left + TILE*SCALE.x,
        pickaxe_field.sprite.getGlobalBounds().top - TILE*SCALE.y
    );
    pickaxe_title.setFont(font);
    pickaxe_title.setCharacterSize(36);
    pickaxe_title.setFillColor(sf::Color(212, 210, 155));
    pickaxe_title.setString("UPGRADE PICKAXE");
    pickaxe_title.setPosition(
        pickaxe_field.sprite.getGlobalBounds().left + 5*TILE*SCALE.x,
        pickaxe_field.sprite.getGlobalBounds().top + UI_TILE*SCALE.y
    );
    pickaxe_description.setFont(font);
    pickaxe_description.setCharacterSize(18);
    pickaxe_description.setFillColor(sf::Color(212, 210, 155));
    pickaxe_description.setString(
        "An ancient dwarf technique allows you to \n"
        "improve your pickaxe, increasing your \n"
        "chances of finding something interesting.");
    pickaxe_description.setPosition(
        pickaxe_field.sprite.getGlobalBounds().left + 5*TILE*SCALE.x,
        pickaxe_field.sprite.getGlobalBounds().top + 2*TILE*SCALE.y
    );
    pieces_to_rect(ui_elem, {0, 26}, {4, 12}, pickaxe_button);
    pickaxe_button.sprite.setPosition(
        pickaxe_field.sprite.getGlobalBounds().left + 17.6*TILE*SCALE.x,
        pickaxe_field.sprite.getGlobalBounds().top + 2.5*TILE*SCALE.y
    );
    pickaxe_cost.setFont(font);
    pickaxe_cost.setCharacterSize(24);
    pickaxe_cost.setFillColor(sf::Color(212, 210, 155));
    pickaxe_cost.setPosition(
        pickaxe_field.sprite.getGlobalBounds().left + 18.25*TILE*SCALE.x,
        pickaxe_field.sprite.getGlobalBounds().top + 3*TILE*SCALE.y
    );

    pieces_to_rect(ui_elem, {0, 32}, {10, 48}, dungeon_field);
    dungeon_field.sprite.setPosition(mbr_bounce.left + UI_TILE*SCALE.x, mbr_bounce.top + 16*UI_TILE*SCALE.x);
    dungeon_anim.setTexture(anim_props);
    dungeon_anim.setScale(SCALE*3.f);
    dungeon_anim.setPosition(
        dungeon_field.sprite.getGlobalBounds().left + TILE*SCALE.x,
        dungeon_field.sprite.getGlobalBounds().top + TILE*SCALE.y
    );
    dungeon_title.setFont(font);
    dungeon_title.setCharacterSize(36);
    dungeon_title.setFillColor(sf::Color(212, 210, 155));
    dungeon_title.setString("CHANGE DUNGEON");
    dungeon_title.setPosition(
        dungeon_field.sprite.getGlobalBounds().left + 5*TILE*SCALE.x,
        dungeon_field.sprite.getGlobalBounds().top + UI_TILE*SCALE.y
    );
    dungeon_description.setFont(font);
    dungeon_description.setCharacterSize(18);
    dungeon_description.setFillColor(sf::Color(212, 210, 155));
    dungeon_description.setString(
        "If I've got it right, with books I can \n"
        "get more valuable resources from \n"
        "this cave. That's very interesting...");
    dungeon_description.setPosition(
       dungeon_field.sprite.getGlobalBounds().left + 5*TILE*SCALE.x,
       dungeon_field.sprite.getGlobalBounds().top + 2*TILE*SCALE.y
   );
    pieces_to_rect(ui_elem, {0, 26}, {4, 12}, dungeon_button);
    dungeon_button.sprite.setPosition(
        dungeon_field.sprite.getGlobalBounds().left + 17.6*TILE*SCALE.x,
        dungeon_field.sprite.getGlobalBounds().top + 2.5*TILE*SCALE.y
    );
    dungeon_cost.setFont(font);
    dungeon_cost.setCharacterSize(24);
    dungeon_cost.setFillColor(sf::Color(212, 210, 155));
    dungeon_cost.setString("not yet");
    dungeon_cost.setPosition(
        dungeon_field.sprite.getGlobalBounds().left + 18.25*TILE*SCALE.x,
        dungeon_field.sprite.getGlobalBounds().top + 3*TILE*SCALE.y
    );

    /*=-= | SHOP | =-=*/
    empty.setFont(font);
    empty.setCharacterSize(32);
    empty.setFillColor(sf::Color(212, 210, 155));
    empty.setString("There is no crystals yet...");
    empty.setPosition((WIDTH - empty.getGlobalBounds().width)/2, (HEIGHT - empty.getGlobalBounds().height)/2);

    crystal_museum_icon.setTexture(hud);
    crystal_museum_icon.setTextureRect({{TILE, TILE}, TILE_SIZE});
    crystal_museum_icon.setPosition(
        pickaxe_level.sprite.getGlobalBounds().left + 2*UI_TILE,
        pickaxe_level.sprite.getGlobalBounds().top + UI_TILE
    );
    crystal_museum_icon.setScale(SCALE * 1.5f);

    pieces_to_rect(ui_elem, {0, 32}, {25, 48}, crystal_view);
    crystal_view.sprite.setPosition(mbr_bounce.left + UI_TILE*SCALE.x, mbr_bounce.top + UI_TILE*5*SCALE.y);

    pieces_to_rect(ui_elem, {0, 26}, {4, 4}, button_left);
    button_left.sprite.setPosition(mbr_bounce.left + UI_TILE*2*SCALE.x, mbr_bounce.top + UI_TILE*25*SCALE.y);
    left_label.setFont(font);
    left_label.setCharacterSize(26);
    left_label.setFillColor(sf::Color(212, 210, 155));
    left_label.setString("<-");
    left_label.setPosition(mbr_bounce.left + UI_TILE*3.5*SCALE.x, mbr_bounce.top + UI_TILE*26*SCALE.y);

    pieces_to_rect(ui_elem, {0, 26}, {4, 4}, button_right);
    button_right.sprite.setPosition(mbr_bounce.left + UI_TILE*44*SCALE.x, mbr_bounce.top + UI_TILE*25*SCALE.y);
    right_label.setFont(font);
    right_label.setCharacterSize(26);
    right_label.setFillColor(sf::Color(212, 210, 155));
    right_label.setString("->");
    right_label.setPosition(mbr_bounce.left + UI_TILE*45.5*SCALE.x, mbr_bounce.top + UI_TILE*26*SCALE.y);

    crystal_title.setFont(font);
    crystal_title.setCharacterSize(36);
    crystal_title.setFillColor(sf::Color(212, 210, 155));
    crystal_title.setPosition(0, mbr_bounce.top + UI_TILE*6*SCALE.y);

    crystal_image.texture.loadFromFile("assets/SGQ_Dungeon/props/props.png");
    crystal_image.sprite.setTexture(crystal_image.texture);
    crystal_image.sprite.setScale(SCALE*4.f);
    crystal_image.sprite.setPosition(WIDTH/2 - TILE*4, mbr_bounce.top + UI_TILE*13*SCALE.y);

    crystal_description.setFont(font);
    crystal_description.setCharacterSize(24);
    crystal_description.setFillColor(sf::Color(212, 210, 155));
    crystal_description.setPosition(0, mbr_bounce.top + UI_TILE*22*SCALE.y);

    pieces_to_rect(ui_elem, {0, 26}, {4, 10}, sell_button);
    sell_button.sprite.setPosition(mbr_bounce.left + UI_TILE*2*SCALE.x, mbr_bounce.top + UI_TILE*6*SCALE.y);
    sell.setFont(font);
    sell.setCharacterSize(26);
    sell.setFillColor(sf::Color(212, 210, 155));
    sell.setString("SELL");
    sell.setPosition(mbr_bounce.left + UI_TILE*4*SCALE.x, mbr_bounce.top + UI_TILE*7*SCALE.y);

    pieces_to_rect(ui_elem, {8, 0}, {4, 10}, sold_label);
    sold_label.sprite.setPosition(mbr_bounce.left + UI_TILE*2*SCALE.x, mbr_bounce.top + UI_TILE*6*SCALE.y);
    sold.setFont(font);
    sold.setCharacterSize(26);
    sold.setFillColor(sf::Color(212, 210, 155));
    sold.setString("SOLD");
    sold.setPosition(mbr_bounce.left + UI_TILE*4*SCALE.x, mbr_bounce.top + UI_TILE*7*SCALE.y);
}

func UserInterface::base_ui() -> void
{
    combined_texture.draw(coin_icon);
    coin_label.setString(std::to_string(parent->get_coins()));
    combined_texture.draw(coin_label);
    combined_texture.draw(crystal_icon);
    crystal_label.setString(std::to_string(parent->get_crystal_count()));
    combined_texture.draw(crystal_label);
}
func UserInterface::settings() -> void
{
    combined_texture.clear(sf::Color(0, 0, 0, 160));
    combined_texture.draw(menu_brick.sprite);
    combined_texture.draw(title_brick.sprite);

    title_label.setString("PAUSE");
    sf::Vector2f old_pos = title_label.getPosition();
    title_label.setPosition({WIDTH/2-title_label.getGlobalBounds().getSize().x/2, old_pos.y});
    combined_texture.draw(title_label);
}
func UserInterface::upgrader() -> void
{
    const std::shared_ptr<Player> plr = parent->get_player();

    combined_texture.clear(sf::Color(0, 0, 0, 160));
    combined_texture.draw(menu_brick.sprite);
    combined_texture.draw(title_brick.sprite);
    combined_texture.draw(upgrader_coins.sprite);
    combined_texture.draw(pickaxe_level.sprite);
    combined_texture.draw(pickaxe_icon);
    combined_texture.draw(up_coins_icon);

    pickaxe_label.setString(std::to_string(plr->get_level()) + " level");
    combined_texture.draw(pickaxe_label);

    up_coins_label.setString(std::to_string(parent->get_coins()) + " coins");
    combined_texture.draw(up_coins_label);

    combined_texture.draw(pickaxe_field.sprite);
    combined_texture.draw(pickaxe_anim);
    combined_texture.draw(pickaxe_title);
    combined_texture.draw(pickaxe_description);
    combined_texture.draw(pickaxe_button.sprite);

    const int lvl_cost = plr->get_level_cost();
    if (lvl_cost == 0)
        pickaxe_cost.setString("MAX");
    else
        pickaxe_cost.setString(std::to_string(lvl_cost) + " coins");
    combined_texture.draw(pickaxe_cost);

    combined_texture.draw(dungeon_field.sprite);
    combined_texture.draw(dungeon_anim);
    combined_texture.draw(dungeon_title);
    combined_texture.draw(dungeon_description);
    combined_texture.draw(dungeon_button.sprite);
    combined_texture.draw(dungeon_cost);

    title_label.setString("UPGRADE");
    sf::Vector2f old_pos = title_label.getPosition();
    title_label.setPosition({WIDTH/2-title_label.getGlobalBounds().getSize().x/2, old_pos.y});
    combined_texture.draw(title_label);
}
func UserInterface::museum() -> void
{
    combined_texture.clear(sf::Color(0, 0, 0, 160));
    combined_texture.draw(menu_brick.sprite);
    combined_texture.draw(title_brick.sprite);


    combined_texture.draw(upgrader_coins.sprite);
    combined_texture.draw(up_coins_icon);
    up_coins_label.setString(std::to_string(parent->get_coins()) + " coins");
    combined_texture.draw(up_coins_label);

    if (parent->get_crystal_count() != 0)
    {
        const std::shared_ptr<ClumpItem> item = parent->get_crystals()[current_crystal];

        combined_texture.draw(pickaxe_level.sprite);
        combined_texture.draw(crystal_museum_icon);
        pickaxe_label.setString(std::to_string(current_crystal+1) + "/" + std::to_string(parent->get_crystal_count()));
        combined_texture.draw(pickaxe_label);

        combined_texture.draw(crystal_view.sprite);
        combined_texture.draw(button_left.sprite);
        combined_texture.draw(left_label);
        combined_texture.draw(button_right.sprite);
        combined_texture.draw(right_label);

        crystal_title.setString(item->name);
        crystal_title.setPosition((WIDTH - crystal_title.getGlobalBounds().width)/2, crystal_title.getPosition().y);

        std::stringstream desc;
        desc << "Rare: " << rare_str[item->rare]
            << "\nAppeal: " << rare_str[item->tex_rare]
            << "\nCost: " << parent->rare_to_cost(item->rare, item->tex_rare, item->cost_mod);
        crystal_description.setString(desc.str());
        crystal_description.setPosition((WIDTH - crystal_description.getGlobalBounds().width)/2, crystal_description.getPosition().y);

        combined_texture.draw(crystal_title);
        combined_texture.draw(crystal_description);

        sf::Vector2i coord;
        switch (item->tex_rare)
        {
            case COMMON: coord = {0, 4}; break;
            case UNCOMMON: coord = {1, 4}; break;
            case RARE: coord = {2, 4}; break;
            case EPIC: coord = {3, 4}; break;
            case LEGENDARY: coord = {0, 5}; break;
            default: coord = {0, 4}; break;
        }
        crystal_image.sprite.setTextureRect({coord * TILE, TILE_SIZE});
        combined_texture.draw(crystal_image.sprite);
        if (item->is_sold)
        {
            combined_texture.draw(sold_label.sprite);
            combined_texture.draw(sold);
        } else
        {
            combined_texture.draw(sell_button.sprite);
            combined_texture.draw(sell);
        }
    } else
        combined_texture.draw(empty);

    title_label.setString("MUSEUM");
    sf::Vector2f old_pos = title_label.getPosition();
    title_label.setPosition({WIDTH/2-title_label.getGlobalBounds().getSize().x/2, old_pos.y});
    combined_texture.draw(title_label);
}

func UserInterface::drawable() -> sf::Sprite
{
    combined_texture.create(WIDTH, HEIGHT);
    combined_texture.clear(sf::Color::Transparent);

    switch (mode)
    {
    case UIMode::BASE: base_ui(); break;
    case UIMode::SETTINGS: settings(); break;
    case UIMode::UPGRADER: upgrader(); break;
    case UIMode::MUSEUM: museum(); break;
    default: base_ui(); break;
    }

    combined_texture.display();
    return sf::Sprite(combined_texture.getTexture());
}
func UserInterface::click(const sf::Vector2i& click_pos) -> void
{
    if (click_cd > 0) return;
    click_cd = .5f;

    if (mode == UIMode::MUSEUM)
    {
        if (button_left.sprite.getGlobalBounds().contains(click_pos.x, click_pos.y) && current_crystal != 0)
            current_crystal--;
        if (button_right.sprite.getGlobalBounds().contains(click_pos.x, click_pos.y) && current_crystal != parent->get_crystal_count()-1)
            current_crystal++;

        const std::shared_ptr<ClumpItem> item = parent->get_crystals()[current_crystal];
        if (sell_button.sprite.getGlobalBounds().contains(click_pos.x, click_pos.y) && !item->is_sold)
        {
            parent->add_coins(parent->rare_to_cost(item->rare, item->tex_rare, item->cost_mod));
            parent->sell_crystal(current_crystal);
        }
    }
    if (mode == UIMode::UPGRADER)
    {
        std::cout << "here!!\n";
        std::shared_ptr<Player> plr = parent->get_player();
        if (pickaxe_button.sprite.getGlobalBounds().contains(click_pos.x, click_pos.y) && plr->get_level_cost() <= parent->get_coins())
        {
            parent->remove_coins(plr->get_level_cost());
            plr->level_up();
        }
    }
}

func UserInterface::update_anims(const float &delta) -> void
{
    if (click_cd > 0) click_cd -= delta;
    if (click_cd <= 0) click_cd = 0;

    /* Upgrade anims */
    pickaxe_anim_time += delta;
    if (pickaxe_anim_time >= pickaxe_anim_speed)
    {
        pickaxe_anim_time = 0;
        pickaxe_frame.left = (pickaxe_frame.left + WEAPON_TILE) % (pickaxe_frame_count * WEAPON_TILE);
    }
    pickaxe_anim.setTextureRect(pickaxe_frame);
    
    dungeon_anim_time += delta;
    if (dungeon_anim_time >= dungeon_anim_speed)
    {
        dungeon_anim_time = 0;
        dungeon_frame.left = 4*TILE + (dungeon_frame.left + TILE) % (dungeon_frame_count * TILE);
    }
    dungeon_anim.setTextureRect(dungeon_frame);
}

func UserInterface::call_rebuild() const -> void
{
    parent->generate_cave();
}

func UserInterface::set_mode(const UIMode& new_mode) -> void
{
    mode = new_mode;
}

func UserInterface::get_mode() const -> UIMode
{
    return mode;
}
