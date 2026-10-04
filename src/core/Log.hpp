#pragma once
#include <memory>
#include <string>
#include <spdlog/spdlog.h>

namespace Core {

// Engine-wide logging built on spdlog.
// Every logger writes to the same console and amity.log, so engine and game output stays in order.
// Loggers are created on first use, so logging works from anywhere (any thread, before Application exists, in tests).
//
//   Log::render().warn("framebuffer incomplete: {}", status);
//   auto log = Log::create("minecraft");
//   log->info("world seed {}", seed);
class Log
{
public:
    // get or create a named logger that shares the engine's console + file output
    static std::shared_ptr<spdlog::logger> create(const std::string& name);

    // minimum level for every logger, existing and future (default: debug in Debug builds, info in Release)
    static void setLevel(spdlog::level::level_enum level);

    // engine subsystem loggers
    static spdlog::logger& core();
    static spdlog::logger& render();
    static spdlog::logger& audio();
    static spdlog::logger& script();
};

} // namespace Core
