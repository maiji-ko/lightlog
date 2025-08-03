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

private:
    bool m_enableColor = true;
    std::string m_tag = "default_console_tag";

    // log pattern
    std::string m_pattern = "[%Y-%m-%d %H:%M:%S.%e] [%l] %v";
};
}