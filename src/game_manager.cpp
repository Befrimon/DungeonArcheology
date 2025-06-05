#include "game_manager.hpp"

#include <player.hpp>
#include <user_interface.hpp>
#include <active/upgrader.hpp>
#include <active/museum.hpp>
#include <active/updater.hpp>
#include <wall.hpp>
#include <ground.hpp>
#include <clumps/default_clump.hpp>
#include <iostream>


func GameManager::generate_cave() -> void
{
    coins -= rebuild_cost;

    const toml::table room_data = toml::parse_file("assets/rooms.toml");
    const toml::node_view<const toml::node> cave = room_data["cave"];
    clumps.clear();

    const sf::Vector2i cave_size{
        cave["size"]["x"].value<int>().value(),
        cave["size"]["y"].value<int>().value()
    };
    const sf::Vector2f cave_delta{
        cave["delta"]["x"].value<float>().value() * TILE,
        cave["delta"]["y"].value<float>().value() * TILE
    };

    for (int x = 0; x < cave_size.x; x++)
        for (int y = 0; y < cave_size.y; y++)
        {
            const auto wall_type = static_cast<WallID>(cave["walls"][y][x].value<int>().value());
            const auto ground_type = static_cast<WallID>(cave["grounds"][y][x].value<int>().value());
            grounds.push_back(std::make_shared<Ground>(
                ground_type, Material::STONE, cave_delta + sf::Vector2f{TILE_F*x, TILE_F*y}
            ));
            if (ground_type == WallID::NONE && std::rand() % 100 < 40)
                clumps.push_back(std::make_shared<DefaultClump>(cave_delta + sf::Vector2f{TILE_F*x, TILE_F*y}));
            if (wall_type == WallID::NONE) continue;
            walls.push_back(std::make_shared<Wall>(
                wall_type, Material::STONE, cave_delta + sf::Vector2f{TILE_F*x, TILE_F*y}
            ));
        }
}

GameManager::GameManager()
    :window(sf::VideoMode(WIDTH, HEIGHT), "Dungeon Archeology"),
    player(std::make_shared<Player>()), gui(std::make_shared<UserInterface>(this))
{
    const toml::table room_data = toml::parse_file("assets/rooms.toml");
    actions.push_back(std::make_shared<Upgrader>());
    actions.push_back(std::make_shared<Museum>());
    actions.push_back(std::make_shared<Updater>());

    /* read laboratory */
    const toml::node_view<const toml::node> laboratory = room_data["laboratory"];

    const sf::Vector2i lab_size{
        laboratory["size"]["x"].value<int>().value(),
        laboratory["size"]["y"].value<int>().value()
    };
    const sf::Vector2f lab_delta{
        laboratory["delta"]["x"].value<float>().value() * TILE,
        laboratory["delta"]["y"].value<float>().value() * TILE
    };

    player->set_position(lab_delta + sf::Vector2f{
        room_data["player_spawn"]["x"].value<float>().value() * TILE,
        room_data["player_spawn"]["y"].value<float>().value() * TILE
    });

    for (int x = 0; x < lab_size.x; x++)
        for (int y = 0; y < lab_size.y; y++)
        {
            const auto wall_type = static_cast<WallID>(laboratory["walls"][y][x].value<int>().value());
            const auto ground_type = static_cast<WallID>(laboratory["grounds"][y][x].value<int>().value());
            grounds.push_back(std::make_shared<Ground>(
                ground_type, Material::BRICK, lab_delta + sf::Vector2f{TILE_F*x, TILE_F*y}
            ));
            if (wall_type == WallID::NONE) continue;
            walls.push_back(std::make_shared<Wall>(
                wall_type, Material::BRICK, lab_delta + sf::Vector2f{TILE_F*x, TILE_F*y}
            ));
        }

    /* read cave */
    generate_cave();

    /* main cycle */
    window.setFramerateLimit(FPS);
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        /* events */
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                if (gui->get_mode() == UIMode::BASE) gui->set_mode(UIMode::SETTINGS);
                else gui->set_mode(UIMode::BASE);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
                for (const auto action : actions)
                    action->interactive(gui, player);
            //if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                //gui->scroll_museum(event.mouseWheelScroll.delta);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            const sf::Vector2i click_pos = sf::Mouse::getPosition(window);
            gui->click(click_pos);
        }

        if (gui->get_mode() == UIMode::BASE)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rm_countdown == -1)
            {   /* run pickaxe animation and check clumps click */
                const sf::Vector2i click_pos = sf::Mouse::getPosition(window);
                player->click(click_pos);
                for (rm_target = 0; rm_target < clumps.size(); rm_target++)
                {
                    auto clump = std::shared_ptr(clumps[rm_target]->try_destroy(click_pos, player));
                    if (clump->message == "OK")
                    {
                        rm_countdown = 1;
                        if (clump->rare > 0) inventory.push_back(clump);
                        break;
                    }
                }
            }

            /* updates */
            if (rm_countdown > 0) rm_countdown -= dt;
            if (rm_countdown <= 0 && rm_countdown > -1)
            {
                clumps[rm_target].reset();
                clumps.erase(clumps.begin() + rm_target);
                rm_countdown = -1;
            }

            player->update(dt);
            player->check_bounds(walls);
        }

        gui->update_anims(dt);

        /* render */
        window.clear(BACKGROUND);

        for (const auto& ground : grounds)
            window.draw(*ground);
        for (const auto& wall : walls)
            window.draw(wall->drawable());
        for (const auto& clump : clumps)
            window.draw(clump->drawable());

        for (const auto action : actions)
            window.draw(action->drawable());
        window.draw(player->drawable());
        window.draw(gui->drawable());

        window.display();
    }
}

func GameManager::get_coins() const -> int
{
    return coins;
}
func GameManager::remove_coins(const int &count) -> void
{
    coins -= count;
}
func GameManager::add_coins(const int& count) -> void
{
    coins += count;
}

func GameManager::get_player() const -> std::shared_ptr<Player>
{
    return player;
}
func GameManager::get_crystal_count() const -> int
{
    return inventory.size();
}
func GameManager::get_crystals() const -> std::vector<std::shared_ptr<ClumpItem>>
{
    return inventory;
}
func GameManager::sell_crystal(const int &index) -> void
{
    inventory[index]->is_sold = true;
}
func GameManager::rare_to_cost(const ClumpRare &rare, const ClumpRare &tex_rare, const float &mod) -> int
{
    return pow(tex_rare*3, rare)*10*mod;
}
