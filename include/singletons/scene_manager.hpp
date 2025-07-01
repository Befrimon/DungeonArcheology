#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <memory>
#include <stack>

#include "../scene.hpp"

class SceneManager final
{
  SceneManager() = default;
  ~SceneManager() = default;
  static SceneManager* instance;

  std::stack<std::unique_ptr<Scene>> scenes_;

public:
  /* Delete on copy or assignment */
  SceneManager(const SceneManager &object) = delete;
  SceneManager &operator=(const SceneManager &object) = delete;
  static SceneManager* getInstance();

  /* Scene stack operation methods */
  void pushScene(std::unique_ptr<Scene> scene);
  void popScene();
  void clearScenes();
  void changeScene(std::unique_ptr<Scene> scene);
  Scene* getCurrentScene() const;

  /* Game methods */
  void handleEvent(const sf::Event &event);
  void update(const float &delta);
  void render(sf::RenderWindow &window);
};

#endif
