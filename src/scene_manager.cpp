#include "scene_manager.hpp"

SceneManager &SceneManager::GetInstance()
{
  static SceneManager instance;
  return instance;
}

void SceneManager::PushScene(std::unique_ptr<Scene> scene)
{
  if (!scenes_.empty())
    scenes_.top()->Exit();
  scenes_.push(std::move(scene));
  scenes_.top()->Enter();
}

void SceneManager::PopScene()
{
  if (!scenes_.empty())
  {
    scenes_.top()->Exit();
    scenes_.pop();
  }
  if (!scenes_.empty())
    scenes_.top()->Enter();
}

void SceneManager::ClearScenes()
{
  while (!scenes_.empty())
    PopScene();
}

void SceneManager::ChangeScene(std::unique_ptr<Scene> scene)
{
  ClearScenes();
  PushScene(std::move(scene));
}

Scene* SceneManager::GetCurrentScene() const
{
  return scenes_.empty() ? nullptr : scenes_.top().get();
}

void SceneManager::HandleEvent(const sf::Event &event)
{
  if (!scenes_.empty())
    scenes_.top()->HandleEvent(event);
}

void SceneManager::Update(const float &delta)
{
  if (!scenes_.empty())
    scenes_.top()->Update(delta);
}

void SceneManager::Render(sf::RenderWindow &window)
{
  if (!scenes_.empty())
    scenes_.top()->Render(window);
}
