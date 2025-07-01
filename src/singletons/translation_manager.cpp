#include "../../include/singletons/translation_manager.hpp"
#include <locale>

TranslationManager::TranslationManager()
{
  setlocale(LC_ALL, "");
  load(setlocale(LC_CTYPE, nullptr));
}

TranslationManager* TranslationManager::instance;
TranslationManager* TranslationManager::getInstance()
{
  if (instance == nullptr)
    instance = new TranslationManager();
  return instance;
}

void TranslationManager::load(const std::string& lang)
{
  toml::table data;
  try {
    data = toml::parse_file("locales/" + lang + ".toml");
  } catch (const toml::parse_error& err)
  {
    std::stringstream text;
    text << "Error parsing TOML: " << err;
    SPDLOG_CRITICAL(text.str());
  }

  std::string group_key;
  for (auto&& [key, value] : data)
  {
    group_key = key.str();
    if (value.is_table())
      for (auto&& [subkey, subvalue] : *value.as_table())
      {
        std::stringstream cur_key;
        cur_key << group_key << "::" << subkey;
        locale_[cur_key.str()] = subvalue.value_or("");
      }
    else
      locale_[group_key] = value.value_or("");
  }

  SPDLOG_INFO("Loaded locale: " + locale_["title"]);
}

std::string TranslationManager::get(const std::string& key)
{
  if (locale_.contains(key))
    return locale_[key];
  return "";
}

