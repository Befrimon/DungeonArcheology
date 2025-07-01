#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

class ResourceManager final
{
  ResourceManager();
  ~ResourceManager() = default;
  static ResourceManager* instance;

  sf::Font font_;

public:
  /* Delete on copy or assignment */
  ResourceManager(const ResourceManager &object) = delete;
  ResourceManager &operator=(const ResourceManager &object) = delete;
  static ResourceManager* getInstance();

  sf::Font &getFont();
};

#endif
