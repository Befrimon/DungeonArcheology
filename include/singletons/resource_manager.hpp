#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

class ResourceManager final
{
  ResourceManager();
  ~ResourceManager() = default;
  static ResourceManager* instance;

  std::unordered_map<std::string, sf::Font> fonts_;
  std::unordered_map<std::string, sf::Texture> textures_;

public:
  /* Delete on copy or assignment */
  ResourceManager(const ResourceManager &object) = delete;
  ResourceManager &operator=(const ResourceManager &object) = delete;
  static ResourceManager* getInstance();

  sf::Font &getFont(const std::string &key);
  sf::Texture &getTexture(const std::string &key);
};

#endif
