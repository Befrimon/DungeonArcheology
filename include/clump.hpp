#ifndef CLUMP_HPP
#define CLUMP_HPP

class Player;

struct ClumpItem
{
    std::string message;

    std::string name;
    float cost_mod;
    ClumpRare rare;
    ClumpRare tex_rare;
    bool is_sold = false;
};

class Clump
{
protected:
    RenderObject clump;
    std::string name;

    ClumpRare rare;
    ClumpRare texture_rare;
    std::vector<int> rare_chances = {0, 0, 0, 0, 0};
    std::vector<int> tex_chances =  {0, 0, 0, 0};

    func define_rare() -> void;
    func define_tex() -> void;

public:
    explicit Clump(const sf::Vector2f &position);
    virtual ~Clump() = default;

    virtual func try_destroy(const sf::Vector2i &click_pos, const std::shared_ptr<Player> &player) -> std::shared_ptr<ClumpItem> = 0;
    virtual func drawable() const -> sf::Sprite;
};

#endif
