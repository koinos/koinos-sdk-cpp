cmake_minimum_required(VERSION 3.5)

project(koinos_libraries)

find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    message(STATUS "Using ccache")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif()

set(CMAKE_C_FLAGS " ${CMAKE_C_FLAGS} -O3 -Wall ")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -O3 -Wall ")

find_package(Boost 1.57 REQUIRED)

add_subdirectory( koinos_api_cpp )
add_subdirectory( koinos_api_c )
add_subdirectory( koinos_wasi_api )
add_subdirectory( vendor )
