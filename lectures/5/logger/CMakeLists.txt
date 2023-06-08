cmake_minimum_required(VERSION 3.20.0)
project(logger)

set(CMAKE_CXX_STANDARD_REQUIRED 17)

add_library(logger src/logger.cpp)
target_include_directories(logger PUBLIC include)
