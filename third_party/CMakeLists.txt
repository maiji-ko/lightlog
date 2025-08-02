project(third_party)

include(FetchContent)

# fmt
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 11.2.0
)
FetchContent_MakeAvailable(fmt)

if(NOT TARGET fmt::fmt)
    message(FATAL_ERROR "fmt library not available")
endif()
