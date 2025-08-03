#pragma once

#include "logger.h"
#include <string>
#include <fstream>
#include <mutex>

namespace loglight
{
    class FileLogger : public Logger
    {
    public:
        ///@brief 构造函数，接受日志文件路径
        ///@param filePath 日志文件路径
        explicit FileLogger(const std::string &filePath);

        ///@brief 析构函数，关闭文件
        ~FileLogger() override;

        ///@brief 设置日志文件路径
        ///@param filePath 日志文件路径
        void setFilePath(const std::string &filePath);

        ///@brief 设置是否追加到文件
        ///@param appendMode 是否追加模式,默认追加模式
        void setAppendMode(bool append);

        ///@brief 实现Logger的纯虚函数
        ///@param level 日志级别
        ///@param message 日志消息
        void log(LogLevel level, const std::string &message) override;

        ///@brief 实现Logger的纯虚函数
        ///@param level 日志级别
        ///@param file 文件路径
        ///@param line 行号
        ///@param function 函数名
        ///@param message 日志消息
        void logWithLocation(LogLevel level,
            const char *file, int line, const char *function,
            const std::string &message) override;

        void setPattern(const std::string& pattern) override;

        ///@brief 设置日志标签
        ///@param tag 日志标签
        void setTag(const std::string &tag) override;

    private:
        std::string m_filePath;                    // 日志文件路径
        std::ofstream m_fileStream;                // 文件流
        bool m_appendMode;                         // 是否追加模式
        std::mutex m_mutex;                        // 互斥锁，保证线程安全
        std::string m_tag = "default_console_tag"; // 日志标签

        std::string m_pattern = "[%Y-%m-%d %H:%M:%S.%e] [%l] %v"; // 日志记录格式

        // 打开文件
        bool openFile();

        // 关闭文件
        void closeFile();

        // 格式化日志消息
        std::string formatMessage(LogLevel level, const std::string &message);
        std::string formatMessageWithLocation(LogLevel level,
            const char *file, int line, const char *function,
            const std::string &message);
    };
}