#include "console_logger.h"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>

#include <unistd.h>
#include <sys/syscall.h>

namespace loglight {
void ConsoleLogger::setConsoleColor(bool enable)
{
    m_enableColor = enable;
}

void ConsoleLogger::setPattern(const std::string& pattern)
{
    m_pattern = pattern;
}

std::string ConsoleLogger::levelToString(LogLevel level)
{
     switch (level) {
        case LogLevel::INFO:
            return "I";
        case LogLevel::DEBUG:
            return "D";
        case LogLevel::WARNING:
            return "W";
        case LogLevel::ERROR:
            return "E";
        default:
            return "U";
    }
}

std::string ConsoleLogger::extractFileName(const char* filePath)
{
    if (!filePath) return "";

    std::string path(filePath);
    size_t pos = path.find_last_of("/\\");
    if (pos != std::string::npos) {
        return path.substr(pos + 1);
    }
    return path;
}

std::string ConsoleLogger::formatMessageWithLocation(LogLevel level, \
    const char* file, int line, const char* function, \
    const std::string& message)
{
    if (m_pattern.empty()) {
        return "[" + levelToString(level) + "] " + message;
    }

    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&timeT), "%Y-%m-%d %H:%M:%S");

    std::string formatted = m_pattern;

    size_t pos = formatted.find("%Y"); // Year
    if (pos != std::string::npos) {
        ss.str("");
        ss << std::put_time(std::localtime(&timeT), "%Y");
        formatted.replace(pos, 2, ss.str());
    }

    pos = formatted.find("%m"); // Month
    if (pos != std::string::npos) {
        ss.str("");
        ss << std::put_time(std::localtime(&timeT), "%m");
        formatted.replace(pos, 2, ss.str());
    }

    pos = formatted.find("%d"); // Day
    if (pos != std::string::npos) {
        ss.str("");
        ss << std::put_time(std::localtime(&timeT), "%d");
        formatted.replace(pos, 2, ss.str());
    }

    pos = formatted.find("%H"); // Hour
    if (pos != std::string::npos) {
        ss.str("");
        ss << std::put_time(std::localtime(&timeT), "%H");
        formatted.replace(pos, 2, ss.str());
    }

    pos = formatted.find("%M"); // Minute
    if (pos != std::string::npos) {
        ss.str("");
        ss << std::put_time(std::localtime(&timeT), "%M");
        formatted.replace(pos, 2, ss.str());
    }

    pos = formatted.find("%S"); // Second
    if (pos != std::string::npos) {
        ss.str("");
        ss << std::put_time(std::localtime(&timeT), "%S");
        formatted.replace(pos, 2, ss.str());
    }

    pos = formatted.find("%e"); // millisecond
    if (pos != std::string::npos) {
        ss.str("");
        ss << std::setfill('0') << std::setw(3) << ms.count();
        formatted.replace(pos, 2, ss.str());
    }

    pos = formatted.find("%P"); // process id
    if (pos != std::string::npos) {
        formatted.replace(pos, 2, std::to_string(getpid()));
    }

    pos = formatted.find("%t"); // thread id
    if (pos != std::string::npos) {
        formatted.replace(pos, 2, std::to_string(syscall(SYS_gettid)));
    }

    pos = formatted.find("%l"); // log level
    if (pos != std::string::npos) {
        formatted.replace(pos, 2, levelToString(level));
    }

    pos = formatted.find("%s"); // source file
    if (pos != std::string::npos) {
        formatted.replace(pos, 2, file ? extractFileName(file) : "");
    }

    pos = formatted.find("%#"); // line number
    if (pos != std::string::npos) {
        formatted.replace(pos, 2, std::to_string(line));
    }

    pos = formatted.find("%!"); // function name
    if (pos != std::string::npos) {
        formatted.replace(pos, 2, function ? function : "");
    }

    pos = formatted.find("%v"); // message
    if (pos != std::string::npos) {
        formatted.replace(pos, 2, message);
    }

    return formatted;
}
std::string ConsoleLogger::formatMessage(LogLevel level, const std::string& message)
{
    return formatMessageWithLocation(level, nullptr, 0, nullptr, message);
}

void ConsoleLogger::log(LogLevel level, const std::string& message)
{
    std::string formattedMessage = formatMessage(level, message);

    if (m_enableColor) {
        std::string color;
        switch (level) {
            case LogLevel::INFO:
                color = "\033[32m";
                break; // 绿色
            case LogLevel::DEBUG:
                color = "\033[34m";
                break; // 蓝色
            case LogLevel::WARNING:
                color = "\033[33m";
                break; // 黄色
            case LogLevel::ERROR:
                color = "\033[31m";
                break; // 红色
        }
        std::cout << color << formattedMessage << "\033[0m" << std::endl;
    } else {
        std::cout << formattedMessage << std::endl;
    }
}

void ConsoleLogger::logWithLocation(LogLevel level, \
    const char* file, int line, const char* function, \
    const std::string& message)
{
    std::string formattedMessage = formatMessageWithLocation(level, file, line, function, message);

    if (m_enableColor) {
        std::string color;
        switch (level) {
            case LogLevel::INFO:
                color = "\033[32m";
                break; // 绿色
            case LogLevel::DEBUG:
                color = "\033[34m";
                break; // 蓝色
            case LogLevel::WARNING:
                color = "\033[33m";
                break; // 黄色
            case LogLevel::ERROR:
                color = "\033[31m";
                break; // 红色
        }
        std::cout << color << formattedMessage << "\033[0m" << std::endl;
    } else {
        std::cout << formattedMessage << std::endl;
    }
}

}