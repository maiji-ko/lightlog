//
// Created by PolarLightDance on 25-7-26.
//

#include "interface/loglight.h"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

// 线程函数：记录日志并观察线程ID
void ThreadFunction(std::shared_ptr<loglight::Logger> logger, int threadId) {
    for (int i = 0; i < 3; ++i) {
        logger->info("Thread {} - Message {}", threadId, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// 多线程测试
void DiffThreadIdTest() {
    // 创建控制台日志记录器
    auto consoleLogger = loglight::LoggerFactory::createConsoleLogger();
    consoleLogger->setLogLevel(loglight::LogLevel::INFO);
    
    // 设置显示线程ID的格式
    consoleLogger->setPattern("[%Y-%m-%d %H:%M:%S.%e] [T:%t] [%l]: %v");
    
    const int numThreads = 3;
    std::vector<std::thread> threads;
    
    consoleLogger->info("Starting multi-thread test with {} threads", numThreads);
    
    // 创建并启动多个线程
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(ThreadFunction, consoleLogger, i);
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    
    consoleLogger->info("All threads completed");
}

int main() {
    // create a console logger
    auto consoleLogger = std::dynamic_pointer_cast<loglight::ConsoleLogger>(loglight::LoggerFactory::createConsoleLogger());

    // log
    consoleLogger->info("Welcome to loglight");
    consoleLogger->info("This is an info message");
    consoleLogger->warning("This is a warning message");
    consoleLogger->error("This is an error message");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    consoleLogger->info("This is a info message with arguments: {}", 1);
    consoleLogger->warning("This is a warning message with arguments: {}, {}", 1, 2);
    consoleLogger->error("This is an error message with arguments: {}, {}, {}", 1, 2, std::string("hello"));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    consoleLogger->setLogLevel(loglight::LogLevel::DEBUG);
    consoleLogger->info("This is a info message, you should not see this message");
    consoleLogger->debug("This is a debug message, you should see this message");
    consoleLogger->warning("This is a warning message, you should see this message");
    consoleLogger->error("This is an error message, you should see this message");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    consoleLogger->setConsoleColor(false);
    consoleLogger->debug("This is a debug message, you should see this message, but without color");

    consoleLogger->setPattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%P] [%t]: %v");
    consoleLogger->debug("This is an info message, you should see this message, but with a different pattern");

    if (consoleLogger) {
        consoleLogger->setConsoleColor(true);
        consoleLogger->setPattern("[%Y-%m-%d %H:%M:%S.%e] [%P] [%t] [%m] [%s:%# %!] %v");
    }
    consoleLogger->setLogLevel(loglight::LogLevel::INFO);
    std::this_thread::sleep_for(std::chrono::milliseconds(7));
    LOG_INFO(consoleLogger, "This is an info message with location info, {}", 1 + 2);
    LOG_DEBUG(consoleLogger, "This is a debug message with location info, {}, {}", "one", "two");
    LOG_WARNING(consoleLogger, "This is a warning message with location info");
    LOG_ERROR(consoleLogger, "This is an error message with location info {}", "ERROR.");

    DiffThreadIdTest();

    return 0;
}