#include "../../include/singletons/scene_manager.hpp"

SceneManager* SceneManager::instance;
SceneManager* SceneManager::getInstance()
{
  if (instance == nullptr)
    instance = new SceneManager();
  return instance;
}

void SceneManager::pushScene(std::unique_ptr<Scene> scene)
{
  if (!scenes_.empty())
    scenes_.top()->exit();
  scenes_.push(std::move(scene));
  scenes_.top()->enter();
}

void SceneManager::popScene()
{
  if (!scenes_.empty())
  {
    scenes_.top()->exit();
    scenes_.pop();
  }
  if (!scenes_.empty())
    scenes_.top()->enter();
}

void SceneManager::clearScenes()
{
  while (!scenes_.empty())
    popScene();
}

void SceneManager::changeScene(std::unique_ptr<Scene> scene)
{
  clearScenes();
  pushScene(std::move(scene));
}

Scene* SceneManager::getCurrentScene() const
{
  return scenes_.empty() ? nullptr : scenes_.top().get();
}

void SceneManager::handleEvent(const sf::Event &event)
{
  if (!scenes_.empty())
    scenes_.top()->handleEvent(event);
}

void SceneManager::update(const float &delta)
{
  if (!scenes_.empty())
    scenes_.top()->update(delta);
}

void SceneManager::render(sf::RenderWindow &window)
{
  if (!scenes_.empty())
    scenes_.top()->render(window);
}
