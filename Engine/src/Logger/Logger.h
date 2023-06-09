#pragma once

#include <memory>
#include <spdlog/spdlog.h>

using externLogger_t = spdlog::logger;

namespace Engine {

    class Logger
    {
    public:
        static void Init();

        inline static externLogger_t& GetLogger() { return *ms_Logger; }
    private:
        inline static std::unique_ptr<externLogger_t> ms_Logger;

        Logger(const Logger& other) = delete;
        Logger& operator=(Logger& other) = delete;
    };
}

#ifdef _DEBUG

#define LOG_CRITICAL(...) \
    do \
    { \
         ::Engine::Logger::GetLogger().critical(__VA_ARGS__); \
    } \
    while (0)

#define LOG_ERROR(...) \
    do \
    { \
         ::Engine::Logger::GetLogger().error(__VA_ARGS__); \
    } \
    while (0)

#define LOG_WARNING(...) \
    do \
    { \
         ::Engine::Logger::GetLogger().warn(__VA_ARGS__); \
    } \
    while (0)

#define LOG_INFO(...) \
    do \
    { \
         ::Engine::Logger::GetLogger().info(__VA_ARGS__); \
    } \
    while (0)

#define ASSERT(x, ...) \
    do \
    { \
        if(!(x)) \
        { \
            ::Engine::Logger::GetLogger().critical(__VA_ARGS__); \
            __debugbreak(); \
        } \
    } \
    while (0)

#else  // _DEBUG

// These are the release mode definitions for the macros above.
#define LOG_CRITICAL(...)
#define LOG_ERROR(...)
#define LOG_WARNING(...)
#define LOG_INFO(...)
#define ASSERT(x, ...)

#endif  // !defined NDEBUG