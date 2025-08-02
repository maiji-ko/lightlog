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

    ///@brief 记录信息日志
    ///@param format 日志格式
    ///@param args 日志参数
    template<typename... Args>
    inline void info(fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::INFO) {
            log(LogLevel::INFO, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    ///@brief 记录调试日志
    ///@param format 日志格式
    ///@param args 日志参数
    template<typename... Args>
    inline void debug(fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::DEBUG) {
            log(LogLevel::DEBUG, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    ///@brief 记录警告日志
    ///@param format 日志格式
    ///@param args 日志参数
    template<typename... Args>
    inline void warning(fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::WARNING) {
            log(LogLevel::WARNING, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    ///@brief 记录错误日志
    ///@param format 日志格式
    ///@param args 日志参数
    template<typename... Args>
    inline void error(fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::ERROR) {
            log(LogLevel::ERROR, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    ///@brief 记录信息日志,带位置信息
    ///@param file 文件路径
    ///@param line 行号
    ///@param function 函数名
    ///@param format 日志格式
    ///@param args 日志参数
    ///@note 记录信息日志,带位置信息
    template<typename... Args>
    inline void infoWithLocation(const char* file, int line, const char* function, fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::INFO) {
            logWithLocation(LogLevel::INFO, file, line, function, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    ///@brief 记录调试日志,带位置信息
    ///@param file 文件路径
    ///@param line 行号
    ///@param function 函数名
    ///@param format 日志格式
    ///@param args 日志参数
    ///@note 记录调试日志,带位置信息
    template<typename... Args>
    inline void debugWithLocation(const char* file, int line, const char* function, fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::DEBUG) {
            logWithLocation(LogLevel::DEBUG, file, line, function, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    ///@brief 记录警告日志,带位置信息
    ///@param file 文件路径
    ///@param line 行号
    ///@param function 函数名
    ///@param format 日志格式
    ///@param args 日志参数
    ///@note 记录警告日志,带位置信息
    template<typename... Args>
    inline void warningWithLocation(const char* file, int line, const char* function, fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::WARNING) {
            logWithLocation(LogLevel::WARNING, file, line, function, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    ///@brief 记录错误日志,带位置信息
    ///@param file 文件路径
    ///@param line 行号
    ///@param function 函数名
    ///@param format 日志格式
    ///@param args 日志参数
    ///@note 记录错误日志,带位置信息
    template<typename... Args>
    inline void errorWithLocation(const char* file, int line, const char* function, fmt::format_string<Args...> format, Args&&... args) {
        if (getLogLevel() <= LogLevel::ERROR) {
            logWithLocation(LogLevel::ERROR, file, line, function, fmt::format(format, std::forward<Args>(args)...));
        }
    }

    ///@brief 设置日志级别
    ///@param level 日志级别
    void setLogLevel(LogLevel level) {
        m_logLevel = level;
    }

    ///@brief 获取日志级别
    ///@return 当前日志级别
    LogLevel getLogLevel() const {
        return m_logLevel;
    }

    ///@brief 设置日志格式
    ///@param pattern 日志格式
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