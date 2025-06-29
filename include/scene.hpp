#ifndef SCENE_HPP
#define SCENE_HPP

class Scene
{
protected:
  Scene() = default;

public:
  virtual ~Scene() = default;

  virtual void HandleEvent(const sf::Event &event) = 0;
  virtual void Update(const float &delta) = 0;
  virtual void Render(sf::RenderWindow &window) = 0;

  virtual void Enter() {}
  virtual void Exit() {}
};

#endif
