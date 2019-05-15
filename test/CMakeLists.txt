cmake_minimum_required(VERSION 3.1)
project(test_jinja2cpp-cli CXX)

add_executable (${PROJECT_NAME} command_line_test.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})


add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME} --gtest_output=xml)