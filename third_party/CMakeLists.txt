# 不需要创建 project，third_party 只是依赖管理目录
include(FetchContent)

# 优先查找系统中的 fmt 库
find_package(fmt QUIET)

if(NOT fmt_FOUND)
    # 如果系统中没有找到 fmt，则从远程下载
    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 11.2.0
    )
    FetchContent_MakeAvailable(fmt)
endif()

# 检查最终是否成功获取到 fmt 库
if(NOT TARGET fmt::fmt)
    message(FATAL_ERROR "fmt library not available")
endif()