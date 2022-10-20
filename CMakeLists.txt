cmake_minimum_required(VERSION 3.8)

add_library(stringify src/stringify.cpp)
add_library(stringify::stringify ALIAS stringify)
target_compile_features(stringify PUBLIC cxx_std_20)
target_include_directories(stringify PUBLIC include)

# fmt
add_subdirectory(lib/fmt)
target_link_libraries(stringify PUBLIC fmt::fmt)

# Set warning level
if (MSVC)
    target_compile_options(stringify PRIVATE /W4)
else()
    target_compile_options(stringify PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
endif()

# Maybe enable warnings as errors
set(WARNINGS_AS_ERRORS_FOR_STRINGIFY OFF CACHE BOOL "ON iff you want to treat warnings as errors")
if(WARNINGS_AS_ERRORS_FOR_STRINGIFY)
    if(MSVC)
        target_compile_options(stringify PRIVATE /WX)
    else()
        target_compile_options(stringify PRIVATE -Werror)
    endif()
endif()