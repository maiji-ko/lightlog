#include "logger.h"

namespace loglight {

std::unordered_map<LogLevel, std::string> Logger::m_levelToString = {
    {LogLevel::INFO, "I"},
    {LogLevel::DEBUG, "D"},
    {LogLevel::WARNING, "W"},
    {LogLevel::ERROR, "E"},
    {LogLevel::LOG_LEVEL_MAX, "U"}
};

} // namespace loglight
