cmake_minimum_required(VERSION 3.1)
project(jinja2cpp-cli CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


add_library(jinja2cpp-libcli src/command_line.cpp src/command_line.h)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} jinja2cpp-libcli)

# Setup testing
enable_testing()
add_subdirectory(test)
