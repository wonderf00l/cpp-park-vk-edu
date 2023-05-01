cmake_minimum_required(VERSION 3.0.0)
project(hw2 VERSION 0.1.0)

add_subdirectory(lib/IO)


add_executable(hw2 src/main.cpp)
target_link_libraries(hw2 IO)