#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

class ResourceManager final
{
  static sf::Font font_;

public:
  static void Initialize();

  static sf::Font &GetFont();
};

#endif
