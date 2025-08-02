project(loglight_example)

set(example_src_list example_main.cpp)

# 运行时输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_BUILD_RPATH ${CMAKE_SOURCE_DIR}/bin/libs)
set(CMAKE_MACOSX_RPATH ON)

add_executable(${PROJECT_NAME} ${example_src_list})

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE loglight::loglight)

# 设置C++20标准
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)