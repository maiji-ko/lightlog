#pragma once

#include "queue/queue.h"
#include "logger/console_logger.h"
#include "logger_factory/logger_factory.h"

#define LOG_INFO(logger, ...) \
    logger->infoWithLocation(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

#define LOG_DEBUG(logger, ...) \
    logger->debugWithLocation(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

#define LOG_WARNING(logger, ...) \
    logger->warningWithLocation(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

#define LOG_ERROR(logger, ...) \
    logger->errorWithLocation(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
