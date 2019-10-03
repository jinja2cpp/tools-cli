cmake_minimum_required(VERSION 3.1)
project(test_jinja2cpp-cli CXX)

find_package(gtest REQUIRED)

add_executable (${PROJECT_NAME}
        command_line_test.cpp
        param_resolver_test.cpp
        )

target_link_libraries(${PROJECT_NAME} jinja2cpp::cli gtest::gtest)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME} --gtest_output=xml)
