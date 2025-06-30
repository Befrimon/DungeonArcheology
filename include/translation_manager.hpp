#ifndef TRANSLATION_MANAGER_HPP
#define TRANSLATION_MANAGER_HPP

#include <string>
#include <unordered_map>

class TranslationManager final
{
  static std::unordered_map<std::string, std::string> locale_;

public:
  static void Load(const std::string &lang);
  static std::string Get(const std::string &key);
};

#endif
