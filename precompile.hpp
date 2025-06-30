#ifndef PRECOMPILE_HPP
#define PRECOMPILE_HPP

/* include SFML */
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

/* include TOML++ */
#include <toml++/toml.hpp>

/* include spdlog */
#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

inline void initLogging() {
  try
  {
    const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    const auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt", true);

    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
    auto logger = std::make_shared<spdlog::logger>("game", begin(sinks), end(sinks));

#ifdef DEBUG
    logger->set_level(spdlog::level::trace);
#else
    logger->set_level(spdlog::level::info);
#endif
    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [thread %t] %v");

    spdlog::register_logger(logger);
    spdlog::set_default_logger(logger);
  } catch (const spdlog::spdlog_ex& ex) {
    std::cerr << "Log initialization failed: " << ex.what() << std::endl;
  }
}

#endif
