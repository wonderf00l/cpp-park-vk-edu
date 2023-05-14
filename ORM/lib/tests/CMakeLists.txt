add_executable(ORM_tests src/test_ORM.cpp)
target_link_libraries(ORM_tests ORM GTest::gtest_main)

add_test(ORM_tests ORM_tests)
