cmake_minimum_required(VERSION 3.1)
project(jinja2cpp-cli CXX)

#set(CMAKE_CXX_STANDARD 17)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


add_executable(jinja2cpp-cli main.cpp)
target_link_libraries(jinja2cpp-cli ${CONAN_LIBS})

