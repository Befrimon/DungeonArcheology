#ifndef TRANSLATION_MANAGER_HPP
#define TRANSLATION_MANAGER_HPP

#include <string>
#include <unordered_map>

class TranslationManager final
{
  TranslationManager();
  ~TranslationManager() = default;
  static TranslationManager* instance;

  std::unordered_map<std::string, std::string> locale_;

public:
  TranslationManager(const TranslationManager &object) = delete;
  TranslationManager &operator=(const TranslationManager &object) = delete;
  static TranslationManager* getInstance();

  void load(const std::string &lang);
  std::string get(const std::string &key);
};

#endif
