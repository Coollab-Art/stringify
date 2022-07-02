cmake_minimum_required(VERSION 3.8)

add_library(stringify src/stringify.cpp)
add_library(stringify::stringify ALIAS stringify)
target_compile_features(stringify PUBLIC cxx_std_20)
target_include_directories(stringify PUBLIC include)