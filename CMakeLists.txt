cmake_minimum_required(VERSION 3.1)
project(jinja2cpp-cli CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_BINARY_DIR})

set (JINJA2CPP_DEPS_MODE conan-build CACHE STRING "" FORCE)
add_subdirectory (thirdparty/Jinja2Cpp ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/jinja2cpp)

find_package(boost 1.71 COMPONENTS program_options filesystem REQUIRED)
find_package(jsonformoderncpp 3.7.0 REQUIRED)
find_package(yaml-cpp 0.6.0 REQUIRED)
#find_package(jinja2cpp REQUIRED)

add_library(jinja2cpp-libcli
        src/command_line.cpp
        src/command_line_j2.cpp
        src/command_line.h
        src/param_resolver.cpp
        src/param_resolver.h
        src/yaml_reflector.h
        )
add_library(jinja2cpp::cli ALIAS jinja2cpp-libcli)
target_link_libraries(jinja2cpp-libcli PUBLIC jinja2cpp
        jsonformoderncpp::jsonformoderncpp
        yaml-cpp::yaml-cpp
        boost::boost
        )

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} jinja2cpp::cli)
set_target_properties (${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON)

add_executable(j2cpp-cli src/main_j2.cpp)
target_link_libraries(j2cpp-cli jinja2cpp::cli)
set_target_properties (j2cpp-cli PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON)

# Setup testing
enable_testing()
add_subdirectory(test)
