//
// Created by PolarLightDance on 25-7-26.
//

#include "interface/loglight.h"
#include <thread>
#include <chrono>
#include <iostream>

// 演示控制台日志的使用
void demonstrateConsoleLogger()
{
    std::cout << "===== 控制台日志演示 =====" << std::endl;
    // 创建控制台日志记录器
    auto consoleLogger = std::dynamic_pointer_cast<loglight::ConsoleLogger>(loglight::LoggerFactory::createConsoleLogger());
    if (!consoleLogger)
    {
        std::cerr << "Failed to create console logger." << std::endl;
        return;
    }

    // 基本日志输出
    consoleLogger->info("Welcome to loglight");
    consoleLogger->info("This is an info message");
    consoleLogger->warning("This is a warning message");
    consoleLogger->error("This is an error message");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // 带参数的日志
    consoleLogger->info("This is a info message with arguments: {}", 1);
    consoleLogger->warning("This is a warning message with arguments: {}, {}", 1, 2);
    consoleLogger->error("This is an error message with arguments: {}, {}, {}", 1, 2, std::string("hello"));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // 日志级别设置
    consoleLogger->setLogLevel(loglight::LogLevel::DEBUG);
    consoleLogger->info("This is a info message, you should not see this message");
    consoleLogger->debug("This is a debug message, you should see this message");
    consoleLogger->warning("This is a warning message, you should see this message");
    consoleLogger->error("This is an error message, you should see this message");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // 关闭颜色输出
    consoleLogger->setConsoleColor(false);
    consoleLogger->debug("This is a debug message, you should see this message, but without color");

    // 自定义日志格式
    consoleLogger->setPattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%P] [%t]: %v");
    consoleLogger->debug("This is an info message, you should see this message, but with a different pattern");

    // 使用位置信息日志宏
    consoleLogger->setConsoleColor(true);
    consoleLogger->setPattern("[%Y-%m-%d %H:%M:%S.%e] [%P] [%t] [%s:%# %!] %v");
    consoleLogger->setLogLevel(loglight::LogLevel::INFO);
    std::this_thread::sleep_for(std::chrono::milliseconds(7));
    LOG_INFO(consoleLogger, "This is an info message with location info, {}", 1 + 2);
    LOG_DEBUG(consoleLogger, "This is a debug message with location info, {}, {}", "one", "two");
    LOG_WARNING(consoleLogger, "This is a warning message with location info");
    LOG_ERROR(consoleLogger, "This is an error message with location info {}", "ERROR.");
}

// 演示文件日志的使用
void demonstrateFileLogger()
{
    std::cout << "\n===== 文件日志演示 =====" << std::endl;
    // 创建文件日志记录器
    auto fileLogger = std::dynamic_pointer_cast<loglight::FileLogger>(loglight::LoggerFactory::createFileLogger("./log.txt"));
    if (!fileLogger)
    {
        std::cerr << "Failed to create file logger." << std::endl;
        return;
    }

    std::cout << "File logger created successfully." << std::endl;

    // 设置日志级别
    fileLogger->setLogLevel(loglight::LogLevel::INFO);

    // 设置日志格式
    fileLogger->setPattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%s:%# %!] %v");

    // 记录不同级别的日志到文件
    fileLogger->info("This is an info message to file");
    fileLogger->warning("This is a warning message to file");
    fileLogger->error("This is an error message to file");

    // 使用带参数的日志
    fileLogger->info("This is an info message with arguments: {}", 123);
    fileLogger->warning("This is a warning message with arguments: {}, {}", "hello", 456);

    // 使用带位置信息的函数
    fileLogger->infoWithLocation(__FILE__, __LINE__, __FUNCTION__, "This is an info message with arguments: {}", 123);
    fileLogger->warningWithLocation(__FILE__, __LINE__, __FUNCTION__, "This is a warning message with arguments: {}, {}", "hello", 456);

    // 使用带位置信息的日志宏
    LOG_INFO(fileLogger, "This is an info message with location to file");
    LOG_ERROR(fileLogger, "This is an error message with location to file {}", "error detail");

    // 测试不追加模式
    std::cout << "Testing non-append mode..." << std::endl;
    auto fileLoggerNonAppend = std::dynamic_pointer_cast<loglight::FileLogger>(
        loglight::LoggerFactory::createFileLogger("./log_non_append.txt", false));
    if (fileLoggerNonAppend)
    {
        fileLoggerNonAppend->info("This will overwrite the file each time");
        std::cout << "Non-append mode test completed." << std::endl;
    }
}

int main()
{
    demonstrateConsoleLogger();
    demonstrateFileLogger();
    return 0;
}