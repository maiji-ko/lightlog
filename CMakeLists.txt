# 设置最低版本要求
cmake_minimum_required(VERSION 3.18)
project(loglight_pro LANGUAGES CXX VERSION 1.0.0)

# 设置安装路径
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # 对于Unix-like系统（除macOS外），使用 /usr/local（需要sudo权限）
    # 对于用户目录，使用 $HOME/.local 但需要手动添加到搜索路径
    # set(CMAKE_PREFIX_PATH "$ENV{HOME}/.local" ${CMAKE_PREFIX_PATH})
    if(UNIX AND NOT APPLE)
        # 保持默认 /usr/local
        message(STATUS "Default install prefix is /usr/local. You may need to use 'sudo' for installation.")
        message(STATUS "To install to user directory, use: cmake -DCMAKE_INSTALL_PREFIX=$ENV{HOME}/.local ..")
    else()
        # macOS和其他系统默认使用用户目录
        set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "Default install path" FORCE)
    endif()
endif()

# 设置编译模式
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/libs)

# third party
add_subdirectory(third_party)

# 源代码
add_subdirectory(src)

# 启用 example 构建（可通过 -DBUILD_EXAMPLE=OFF 关闭）
option(BUILD_EXAMPLE "Build example" ON)
if (BUILD_EXAMPLE)
    add_subdirectory(example)
endif ()