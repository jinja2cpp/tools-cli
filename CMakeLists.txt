cmake_minimum_required(VERSION 3.1)
project(jinja2cpp-cli CXX)

set(CMAKE_CXX_STANDARD 17)

# if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
#   message(STATUS "Downloading conan.cmake from https://github.com/memsharded/cmake-conan")
#   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/master/conan.cmake"
#                 "${CMAKE_BINARY_DIR}/conan.cmake")
# endif()

# include(${CMAKE_BINARY_DIR}/conan.cmake)
include(conan.cmake)

conan_add_remote(NAME manu343726 URL https://api.bintray.com/packages/manu343726/conan-packages)

conan_cmake_run(REQUIRES CLI11/1.7.1@cliutils/stable
#        jinja2cpp/0.9.1@Manu343726/testing
        OPTIONS
        jinja2cpp:shared=False
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)


conan_basic_setup()

set (TARGET_NAME jinja2cpp)

add_executable(${TARGET_NAME} main.cpp)
target_link_libraries(${TARGET_NAME} ${CONAN_LIBS})

