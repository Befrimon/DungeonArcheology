#ifndef SLICE_SPRITE_HPP
#define SLICE_SPRITE_HPP

class SliceSprite final : public sf::Drawable, public sf::Transformable
{
  sf::Texture texture_;
  std::array<sf::VertexArray, 9> slices_;
  sf::Vector2u tile_size_;
  sf::Vector2f size_;

  void updateGeometry();

public:
  SliceSprite() = default;
  SliceSprite(const sf::Texture &texture);
  SliceSprite(const sf::Texture &texture, const sf::Vector2u &tile_size);
  SliceSprite(const sf::Texture &texture, const sf::Vector2u &tile_size, const sf::Vector2f &size);

  void setTexture(const sf::Texture &texture);
  void setTexture(const sf::Texture &texture, const sf::Vector2u &tile_size);
  void setTileSize(const sf::Vector2u &tile_size);
  void setSize(const sf::Vector2f &size);

  sf::FloatRect getGlobalBounds() const;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif
