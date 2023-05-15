cmake_minimum_required(VERSION 3.5) 
project(increa_proj_test CXX)

# enable_testing() should be in the root CMakeLists.txt
                                                         #
add_executable(${PROJECT_NAME} test_main.cc)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

include(ParseAndAddDrogonTests)

ParseAndAddDrogonTests(${PROJECT_NAME})

add_test(NAME testing COMMAND ${PROJECT_NAME})