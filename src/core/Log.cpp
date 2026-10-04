#include "Log.hpp"
#include <mutex>
#include <vector>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Core {

namespace {

std::mutex s_createMutex;

// shared outputs + global settings, set up once on first use
const std::vector<spdlog::sink_ptr>& sinks()
{
    static const std::vector<spdlog::sink_ptr> s = [] {
        std::vector<spdlog::sink_ptr> result{ std::make_shared<spdlog::sinks::stdout_color_sink_mt>() };
        try {
            result.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("amity.log", true)); // overwrite each run
        } catch (const spdlog::spdlog_ex&) {
            // working directory isn't writable, log to console only
        }

        spdlog::set_pattern("[%H:%M:%S.%e] [%n] [%^%l%$] %v");
#ifndef NDEBUG
        spdlog::set_level(spdlog::level::debug);
#else
        spdlog::set_level(spdlog::level::info);
#endif
        spdlog::flush_on(spdlog::level::warn); // warnings/errors reach amity.log even if we crash right after
        return result;
    }();
    return s;
}

} // namespace

std::shared_ptr<spdlog::logger> Log::create(const std::string& name)
{
    std::scoped_lock lock(s_createMutex);
    if (auto existing = spdlog::get(name)) return existing;

    const auto& s = sinks();
    auto logger = std::make_shared<spdlog::logger>(name, s.begin(), s.end());
    spdlog::initialize_logger(logger); // registers it and applies the global pattern/level/flush settings
    return logger;
}

void Log::setLevel(spdlog::level::level_enum level)
{
    sinks(); // make sure first-use setup has run, so it can't override this later
    spdlog::set_level(level);
}

spdlog::logger& Log::core()   { static auto logger = create("core");   return *logger; }
spdlog::logger& Log::render() { static auto logger = create("render"); return *logger; }
spdlog::logger& Log::audio()  { static auto logger = create("audio");  return *logger; }
spdlog::logger& Log::script() { static auto logger = create("script"); return *logger; }

} // namespace Core
