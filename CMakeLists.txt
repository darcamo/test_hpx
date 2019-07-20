cmake_minimum_required(VERSION 3.10)

project(test_hpx)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

find_package(HPX REQUIRED)

#add_hpx_executable(hello SOURCES hello.cpp)
#target_link_libraries(hello PUBLIC CONAN_PKG::hpx)
#
#add_executable(accumulator
#  accumulator_client.cpp
#  accumulator.hpp
#  accumulator.cpp
#  server/accumulator.hpp)
#target_link_libraries(accumulator PUBLIC CONAN_PKG::hpx)


add_hpx_executable(simple SOURCES simple.cpp)
target_link_libraries(simple PUBLIC CONAN_PKG::hpx)

add_hpx_executable(fibonacci_local SOURCES fibonacci_local.cpp)
target_link_libraries(fibonacci_local PUBLIC CONAN_PKG::hpx)

add_hpx_executable(hello_world_distributed SOURCES hello_world_distributed.cpp)
target_link_libraries(hello_world_distributed PUBLIC CONAN_PKG::hpx)
