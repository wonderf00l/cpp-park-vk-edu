cmake_minimum_required(VERSION 3.8) project(increa_proj_test CXX)

#find_package(Drogon REQUIRED)
    add_executable(${PROJECT_NAME} test_main.cc)

# ##############################################################################
#If you include the drogon source code locally in your project, use this method
#to add drogon
#target_link_libraries(${PROJECT_NAME} _test PRIVATE drogon)
#
#and comment out the following lines
        target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

            ParseAndAddDrogonTests(${PROJECT_NAME})
