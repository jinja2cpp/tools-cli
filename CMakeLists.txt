cmake_minimum_required(VERSION 3.1)
project(jinja2cpp-cli CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


add_executable(${PROJECT_NAME} main.cpp command_line.cpp command_line.h)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

