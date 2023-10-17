cmake_minimum_required(VERSION 3.5)

project(bip32_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(bip32 src/main.cpp src/ckd.cpp)
target_include_directories(bip32 PRIVATE src)
