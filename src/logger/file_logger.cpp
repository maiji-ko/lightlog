#include "file_logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <stdexcept>

namespace loglight {
std::string FileLogger::levelToString(LogLevel level)
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

FileLogger::FileLogger(const std::string& filePath) : 
    m_filePath(filePath), 
    m_appendMode(true)
{
    if (!openFile()) {
        throw std::runtime_error("Failed to open log file: " + filePath);
    }
}

FileLogger::~FileLogger()
{
    closeFile();
}

void FileLogger::setFilePath(const std::string& filePath)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    closeFile();
    m_filePath = filePath;
    openFile();
}

void FileLogger::setAppendMode(bool append)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_appendMode != append) {
        closeFile();
        m_appendMode = append;
        openFile();
    }
}

bool FileLogger::openFile()
{
    std::ios_base::openmode mode = std::ios::out;
    if (m_appendMode) {
        mode |= std::ios::app;
    } else {
        mode |= std::ios::trunc;
    }

    m_fileStream.open(m_filePath, mode);
    return m_fileStream.is_open();
}

void FileLogger::closeFile()
{
    if (m_fileStream.is_open()) {
        m_fileStream.flush();
        m_fileStream.close();
    }
}

std::string FileLogger::formatMessage(LogLevel level, const std::string& message)
{
    return formatMessageWithLocation(level, nullptr, 0, nullptr, message);
}

std::string FileLogger::formatMessageWithLocation(LogLevel level, 
    const char* file, int line, const char* function, 
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

    // 替换时间格式占位符
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

    // 替换日志级别
    pos = formatted.find("%l");
    if (pos != std::string::npos) {
        formatted.replace(pos, 2, levelToString(level));
    }

    // 替换文件信息
    pos = formatted.find("%s");
    if (pos != std::string::npos) {
        if (file) {
            std::string filePath(file);
            size_t lastSlash = filePath.find_last_of("/\\");
            std::string fileName = (lastSlash != std::string::npos) ? filePath.substr(lastSlash + 1) : filePath;
            formatted.replace(pos, 2, fileName);
        } else {
            formatted.replace(pos, 2, "-");
        }
    }

    // 替换行号
    pos = formatted.find("%#");
    if (pos != std::string::npos) {
        if (line > 0) {
            formatted.replace(pos, 2, std::to_string(line));
        } else {
            formatted.replace(pos, 2, "-");
        }
    }

    // 替换函数名
    pos = formatted.find("%!");
    if (pos != std::string::npos) {
        if (function) {
            formatted.replace(pos, 2, function);
        } else {
            formatted.replace(pos, 2, "-");
        }
    }

    // 替换消息
    pos = formatted.find("%v");
    if (pos != std::string::npos) {
        formatted.replace(pos, 2, message);
    }

    return formatted;
}

void FileLogger::log(LogLevel level, const std::string& message)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_fileStream.is_open() && !openFile()) {
        std::cerr << "Failed to write log: cannot open file " << m_filePath << std::endl;
        return;
    }

    std::string formattedMessage = formatMessage(level, message);
    m_fileStream << formattedMessage << std::endl;
    m_fileStream.flush();
}

void FileLogger::logWithLocation(LogLevel level, 
    const char* file, int line, const char* function, 
    const std::string& message)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_fileStream.is_open() && !openFile()) {
        std::cerr << "Failed to write log: cannot open file " << m_filePath << std::endl;
        return;
    }

    std::string formattedMessage = formatMessageWithLocation(level, file, line, function, message);
    m_fileStream << formattedMessage << std::endl;
    m_fileStream.flush();
}
}