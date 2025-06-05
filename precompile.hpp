#ifndef PRECOMPILE_HPP
#define PRECOMPILE_HPP

/* include SFML */
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/* include toml++ */
#include <toml++/toml.h>

/* code style */
#define func auto
struct RenderObject
{
    sf::Texture texture;
    sf::Sprite sprite;
};

/* variables */
constexpr int WIDTH = 1600;
constexpr int HEIGHT = 900;
constexpr int FPS = 60;
const sf::Vector2f SCALE{2.f, 2.f};

constexpr int TILE = 16;
constexpr float TILE_F = TILE;
const sf::Vector2i TILE_SIZE{TILE, TILE};

constexpr int WEAPON_TILE = TILE*3;
constexpr float WEAPON_TILE_F = WEAPON_TILE;
const sf::Vector2i WEAPON_TILE_SIZE{WEAPON_TILE, WEAPON_TILE};

constexpr int UI_TILE = TILE / 2;
constexpr float UI_TILE_F = UI_TILE;
const sf::Vector2i UI_TILE_SIZE{UI_TILE, UI_TILE};

const sf::Color BACKGROUND{88, 68, 34};

/* enumerators */
enum WallID {NONE = 0,
    TOP = 1, BOTTOM = 2, LEFT = 3, RIGHT = 4,
    TOP_LEFT_1 = 5, TOP_RIGHT_1 = 6, BOTTOM_LEFT_1 = 7, BOTTOM_RIGHT_1 = 8,  // Outer corners
    TOP_LEFT_2 = 9, TOP_RIGHT_2 = 10, BOTTOM_LEFT_2 = 11, BOTTOM_RIGHT_2 = 12,  // Inner corners
    GROUND = 13, DOOR = 14, HALL_VERTICAL = 15, HALL_HORIZONTAL = 16,
    HALL_TOP = 17, HALL_BOTTOM = 18, HALL_LEFT = 19, HALL_RIGHT = 20,
    LEFT_AND_TR = 21, BOTTOM_AND_TL = 22, LEFT_GRIDLOCK = 23
};
enum Material {BRICK, STONE};
enum ClumpRare {NOTHING, COMMON, UNCOMMON, RARE, EPIC, LEGENDARY};
enum UIMode {BASE, SETTINGS, UPGRADER, MUSEUM};

#endif
