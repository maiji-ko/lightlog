#pragma once

#include "logger.h"

namespace loglight {
class ConsoleLogger : public Logger {
public:
    ConsoleLogger() = default;

    void setConsoleColor(bool enable);

    void setPattern(const std::string& pattern) override;

    void setTag(const std::string& tag) override;

protected:
    
    // Logger
    void log(LogLevel level, const std::string& message) override;
    void logWithLocation(LogLevel level, \
        const char* file, int line, const char* function, \
        const std::string& message) override;

private:
    std::string formatMessage(LogLevel level, const std::string& message);
    std::string formatMessageWithLocation(LogLevel level, \
        const char* file, int line, const char* function, \
        const std::string& message);
    std::string extractFileName(const char* filePath);

    inline std::string getColor(LogLevel& level) const {
        if (!m_enableColor)
            return "";

        switch (level) {
            case LogLevel::INFO:
                return "\033[32m";    // 绿色
            case LogLevel::DEBUG:
                return "\033[34m";    // 蓝色
            case LogLevel::WARNING:
                return "\033[33m";    // 黄色
            case LogLevel::ERROR:
                return "\033[31m";    // 红色
            case LogLevel::LOG_LEVEL_MAX:
            default:
                return "\033[97m";    // 亮白色
        }
    }

private:
    bool m_enableColor = true;
    std::string m_tag = "default_console_tag";

    // log pattern
    std::string m_pattern = "[%Y-%m-%d %H:%M:%S.%e] [%l] %v";
};
}