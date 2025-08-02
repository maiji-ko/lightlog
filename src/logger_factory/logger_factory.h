#pragma once

#include <memory>
#include <string>

#include "logger/console_logger.h"
#include "logger/file_logger.h"

namespace loglight {
class LoggerFactory {
public:
    LoggerFactory() = delete;
    LoggerFactory(const LoggerFactory&) = delete;
    LoggerFactory& operator=(const LoggerFactory&) = delete;

    ///@brief 创建一个控制台日志记录器
    ///@return 控制台日志记录器
    static std::shared_ptr<Logger> createConsoleLogger();

    ///@param filePath 日志文件路径
    ///@param appendMode 是否追加模式,默认追加模式
    ///@return 文件日志记录器
    static std::shared_ptr<Logger> createFileLogger(const std::string& filePath, bool appendMode = true);
};
}
