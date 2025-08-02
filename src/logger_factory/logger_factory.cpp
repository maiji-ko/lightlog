#include "logger_factory.h"

namespace loglight {
std::shared_ptr<Logger> LoggerFactory::createConsoleLogger()
{
    return std::make_shared<ConsoleLogger>();
}
}