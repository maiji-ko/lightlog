//
// Created by PolarLightDance on 25-7-26.
//

#include "interface/loglight.h"
#include <thread>
#include <chrono>

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
        consoleLogger->setPattern("[%Y-%m-%d %H:%M:%S.%e] [%P] [%t] [%s:%# %!] %v");
    }
    consoleLogger->setLogLevel(loglight::LogLevel::INFO);
    std::this_thread::sleep_for(std::chrono::milliseconds(7));
    LOG_INFO(consoleLogger, "This is an info message with location info, {}", 1 + 2);
    LOG_DEBUG(consoleLogger, "This is a debug message with location info, {}, {}", "one", "two");
    LOG_WARNING(consoleLogger, "This is a warning message with location info");
    LOG_ERROR(consoleLogger, "This is an error message with location info {}", "ERROR.");

    return 0;
}