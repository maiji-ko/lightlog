#pragma once

#include <memory>

#include "logger/console_logger.h"

namespace loglight {
class LoggerFactory {
public:
    LoggerFactory() = delete;
    LoggerFactory(const LoggerFactory&) = delete;
    LoggerFactory& operator=(const LoggerFactory&) = delete;

    // 创建一个控制台日志
    static std::shared_ptr<Logger> createConsoleLogger();
};
}
