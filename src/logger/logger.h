#pragma once

#include <string>
#include <unordered_map>
#include <fmt/core.h>

namespace loglight {

enum class LogLevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR,
    LOG_LEVEL_MAX
};

class Logger{
public:
    Logger() = default;
    virtual ~Logger() = default;

    template<typename... Args>
    inline void info(fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::INFO) {
            log(LogLevel::INFO, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    template<typename... Args>
    inline void debug(fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::DEBUG) {
            log(LogLevel::DEBUG, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    template<typename... Args>
    inline void warning(fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::WARNING) {
            log(LogLevel::WARNING, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    template<typename... Args>
    inline void error(fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::ERROR) {
            log(LogLevel::ERROR, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    // 记录信息日志,带位置信息
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

    // 设置日志级别
    void setLogLevel(LogLevel level) {
        m_logLevel = level;
    }

    LogLevel getLogLevel() const {
        return m_logLevel;
    }

    // 设置日志标签
    virtual void setTag(const std::string& tag) = 0;

    // 设置日志格式
    virtual void setPattern(const std::string& pattern) = 0;

protected:
    // log
    virtual void log(LogLevel level, const std::string& message) = 0;

    // log with location
    virtual void logWithLocation(LogLevel level, \
        const char* file, int line, const char* function, \
        const std::string& message) {
        log(level, message);
    }

    // 日志等级转换为字符串
    std::string& levelToString(LogLevel& level) {
        if (level < LogLevel::LOG_LEVEL_MAX) {
            return m_levelToString[level];
        }
        return m_levelToString[LogLevel::LOG_LEVEL_MAX];
    }

    // log level
    LogLevel m_logLevel = LogLevel::INFO;
private:
    static std::unordered_map<LogLevel, std::string> m_levelToString;
};

} // namespace loglight