cmake_minimum_required(VERSION 3.8)

add_library(stringify INTERFACE)
add_library(stringify::stringify ALIAS stringify)
target_compile_features(stringify INTERFACE cxx_std_20)
target_include_directories(stringify INTERFACE include)