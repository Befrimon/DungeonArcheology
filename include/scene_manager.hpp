#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <memory>
#include <stack>

#include "scene.hpp"

class SceneManager final
{
  SceneManager() = default;
  ~SceneManager() = default;

  std::stack<std::unique_ptr<Scene>> scenes_;

public:
  /* Delete on copy or assignment */
  SceneManager(const SceneManager &object) = delete;
  SceneManager &operator=(const SceneManager &object) = delete;

  static SceneManager &GetInstance();

  /* Scene stack operation methods */
  void PushScene(std::unique_ptr<Scene> scene);
  void PopScene();
  void ClearScenes();
  void ChangeScene(std::unique_ptr<Scene> scene);
  Scene* GetCurrentScene() const;

  /* Game methods */
  void HandleEvent(const sf::Event &event);
  void Update(const float &delta);
  void Render(sf::RenderWindow &window);
};

#endif
