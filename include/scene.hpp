#ifndef SCENE_HPP
#define SCENE_HPP

class Scene
{
protected:
  Scene() = default;

public:
  virtual ~Scene() = default;

  virtual void handleEvent(const sf::Event &event) = 0;
  virtual void update(const float &delta) = 0;
  virtual void render(sf::RenderWindow &window) = 0;

  virtual void enter() {}
  virtual void exit() {}
};

#endif
