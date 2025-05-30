cmake_minimum_required(VERSION 3.20)

set(WARNINGS_AS_ERRORS_FOR_STRINGIFY OFF CACHE BOOL "ON iff you want to treat warnings as errors")

add_library(stringify src/stringify.cpp)
add_library(stringify::stringify ALIAS stringify)
target_compile_features(stringify PUBLIC cxx_std_20)

if(WARNINGS_AS_ERRORS_FOR_STRINGIFY)
    target_include_directories(stringify PUBLIC include)
else()
    target_include_directories(stringify SYSTEM PUBLIC include)
endif()

# fmt
set(FMT_SYSTEM_HEADERS ON CACHE BOOL "" FORCE)
set(FMT_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/fmt)
target_link_libraries(stringify PUBLIC fmt::fmt)
install(FILES "lib/fmt/LICENSE" DESTINATION "license/fmt")

# Set warning level
if(MSVC)
    target_compile_options(stringify PRIVATE /W4)
else()
    target_compile_options(stringify PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
endif()

# Maybe enable warnings as errors
if(WARNINGS_AS_ERRORS_FOR_STRINGIFY)
    if(MSVC)
        target_compile_options(stringify PRIVATE /WX)
    else()
        target_compile_options(stringify PRIVATE -Werror)
    endif()
endif()