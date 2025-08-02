#pragma once

#include <string>
#include <fmt/core.h>

namespace loglight {

enum class LogLevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR
};

class Logger{
public:
    Logger() = default;
    virtual ~Logger() = default;

    // 基础日志记录方法
    // info
    template<typename... Args>
    inline void info(fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::INFO) {
            log(LogLevel::INFO, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    // debug
    template<typename... Args>
    inline void debug(fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::DEBUG) {
            log(LogLevel::DEBUG, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    // warning
    template<typename... Args>
    inline void warning(fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::WARNING) {
            log(LogLevel::WARNING, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    // error
    template<typename... Args>
    inline void error(fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::ERROR) {
            log(LogLevel::ERROR, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    // 带位置信息的日志记录方法
    template<typename... Args>
    inline void infoWithLocation(const char* file, int line, const char* function, fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::INFO) {
            logWithLocation(LogLevel::INFO, file, line, function, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    template<typename... Args>
    inline void debugWithLocation(const char* file, int line, const char* function, fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::DEBUG) {
            logWithLocation(LogLevel::DEBUG, file, line, function, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    template<typename... Args>
    inline void warningWithLocation(const char* file, int line, const char* function, fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::WARNING) {
            logWithLocation(LogLevel::WARNING, file, line, function, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    template<typename... Args>
    inline void errorWithLocation(const char* file, int line, const char* function, fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::ERROR) {
            logWithLocation(LogLevel::ERROR, file, line, function, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    // set log level
    void setLogLevel(LogLevel level) {
        m_logLevel = level;
    }

    // get log level
    LogLevel getLogLevel() const {
        return m_logLevel;
    }

    // set log pattern
    virtual void setPattern(const std::string& pattern) {
        m_pattern = pattern;
    }

protected:
    // log
    virtual void log(LogLevel level, const std::string& message) = 0;

    // log with location
    virtual void logWithLocation(LogLevel level, \
        const char* file, int line, const char* function, \
        const std::string& message) {
        log(level, message);
    }

    // log level
    LogLevel m_logLevel = LogLevel::INFO;

    // log pattern
    std::string m_pattern = "[%Y-%m-%d %H:%M:%S.%e] [%l] %v";
};

} // namespace loglight