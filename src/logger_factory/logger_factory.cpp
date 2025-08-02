#include "logger_factory.h"
#include <iostream>
#include <stdexcept>

namespace loglight {
std::shared_ptr<Logger> LoggerFactory::createConsoleLogger()
{
    return std::make_shared<ConsoleLogger>();
}

std::shared_ptr<Logger> LoggerFactory::createFileLogger(const std::string& filePath, bool appendMode)
{
    try {
        auto logger = std::make_shared<FileLogger>(filePath);
        logger->setAppendMode(appendMode);
        return logger;
    } catch (const std::exception& e) {
        std::cerr << "Failed to create file logger: " << e.what() << std::endl;
        return nullptr;
    }
}
}