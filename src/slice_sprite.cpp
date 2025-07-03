#include "slice_sprite.hpp"

SliceSprite::SliceSprite(const sf::Texture &texture)
{
  setTexture(texture);
}
SliceSprite::SliceSprite(const sf::Texture& texture, const sf::Vector2u& tile_size)
{
  setTexture(texture);
  setTileSize(tile_size);
}
SliceSprite::SliceSprite(const sf::Texture& texture, const sf::Vector2u& tile_size, const sf::Vector2f& size)
{
  setTexture(texture);
  setTileSize(tile_size);
  setSize(size);
}

void SliceSprite::updateGeometry()
{
  const float texCoordsX[4] = { 0.f, tile_size_.x*1.f, tile_size_.x*2.f, tile_size_.x*3.f };
  const float texCoordsY[4] = { 0.f, tile_size_.y*1.f, tile_size_.y*2.f, tile_size_.y*3.f };
  const float vertCoordsX[4] = {
    0.f, static_cast<float>(tile_size_.x),
    static_cast<float>(size_.x - tile_size_.x), static_cast<float>(size_.x)
  };
  const float vertCoordsY[4] = {
    0.f, static_cast<float>(tile_size_.y),
    static_cast<float>(size_.y - tile_size_.y), static_cast<float>(size_.y)
  };

  for (int y = 0; y < 3; ++y)
    for (int x = 0; x < 3; ++x)
    {
      const int index = y * 3 + x;
      slices_[index].setPrimitiveType(sf::Quads);
      slices_[index].resize(4);

      slices_[index][0].position = sf::Vector2f(vertCoordsX[x], vertCoordsY[y]);
      slices_[index][1].position = sf::Vector2f(vertCoordsX[x+1], vertCoordsY[y]);
      slices_[index][2].position = sf::Vector2f(vertCoordsX[x+1], vertCoordsY[y+1]);
      slices_[index][3].position = sf::Vector2f(vertCoordsX[x], vertCoordsY[y+1]);

      slices_[index][0].texCoords = sf::Vector2f(texCoordsX[x], texCoordsY[y]);
      slices_[index][1].texCoords = sf::Vector2f(texCoordsX[x+1], texCoordsY[y]);
      slices_[index][2].texCoords = sf::Vector2f(texCoordsX[x+1], texCoordsY[y+1]);
      slices_[index][3].texCoords = sf::Vector2f(texCoordsX[x], texCoordsY[y+1]);
    }
}

void SliceSprite::setTexture(const sf::Texture &texture)
{
  texture_ = texture;
  if (tile_size_ == sf::Vector2u(0, 0))
    tile_size_ = sf::Vector2u(texture.getSize().x / 3, texture.getSize().y / 3);
  updateGeometry();
}
void SliceSprite::setTexture(const sf::Texture &texture, const sf::Vector2u &tile_size)
{
  texture_ = texture;
  tile_size_ = tile_size;
  updateGeometry();
}
void SliceSprite::setTileSize(const sf::Vector2u &tile_size)
{
  tile_size_ = tile_size;
  updateGeometry();
}
void SliceSprite::setSize(const sf::Vector2f &size)
{
  size_ = size;
  updateGeometry();
}

sf::FloatRect SliceSprite::getGlobalBounds() const
{
  const sf::Vector2f real_size{ size_.x * getScale().x, size_.y * getScale().y };
  return sf::FloatRect(getPosition().x - real_size.x/2, getPosition().y - real_size.y/2, real_size.x, real_size.y);
}

void SliceSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  states.texture = &texture_;
  for (const sf::VertexArray &slice : slices_)
    target.draw(slice, states);
}

