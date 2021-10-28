
cmake_minimum_required(VERSION 3.10.2)

project(koinos_contract VERSION 0.1.0 LANGUAGES CXX)

include(KoinosProto)

add_subdirectory(types)
add_subdirectory(src)
