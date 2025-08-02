project(loglight VERSION 1.0.0)

# 设置源文件列表
set(src_list
    queue/queue.cpp
    logger/console_logger.cpp
    logger_factory/logger_factory.cpp
)

# 设置库输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/libs)

# 创建共享库
add_library(${PROJECT_NAME} SHARED ${src_list})
add_library(loglight::loglight ALIAS loglight)

# 链接依赖项
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)

# 设置C++20标准
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/loglight>
)

# 安装目标
install(TARGETS ${PROJECT_NAME}
    EXPORT loglightTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# 安装头文件
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/loglight
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

# 创建并安装配置文件
install(EXPORT loglightTargets
    FILE loglightTargets.cmake
    NAMESPACE loglight::
    DESTINATION lib/cmake/loglight
)

# 创建包配置文件
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/loglightConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/loglightConfig.cmake
    INSTALL_DESTINATION lib/cmake/loglight
)

# 安装配置文件
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/loglightConfig.cmake
    DESTINATION lib/cmake/loglight
)

# 创建并安装版本文件
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/loglightConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/loglightConfigVersion.cmake
    DESTINATION lib/cmake/loglight
)