cmake_minimum_required(VERSION 3.0.0)
project(ORM_project_part VERSION 0.1.0)

find_package(PkgConfig)
pkg_check_modules(LIBCONFIG REQUIRED IMPORTED_TARGET libconfig++)

enable_testing()
find_package(GTest REQUIRED)
#include(GoogleTest)

add_subdirectory(lib/ORM)

add_executable(ORM_project_part src/main.cpp)
target_link_libraries(ORM_project_part ORM)