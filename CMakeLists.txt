
cmake_minimum_required (VERSION 3.10.2)

project( koinos-cdt )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)
set(VERSION_FULL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set( KOINOS_CDT_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/koins-cdt )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror" )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror" )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas" )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unknown-pragmas" )

include( KoinosWasiSDK )

set(CMAKE_SYSROOT "${KOINOS_WASI_SDK_PATH}/share/wasi-sysroot")
# set(CMAKE_STAGING_PREFIX /home/devel/stage)

include( KoinosLibraries )

### Configure the KoinosWasmToolchain.cmakes
set(CDT_ROOT_DIR "${CMAKE_BINARY_DIR}/install")

configure_file(${CMAKE_SOURCE_DIR}/cmake/KoinosWasmToolchain.cmake.in ${CMAKE_BINARY_DIR}/lib/cmake/koinos-cdt/KoinosWasmToolchain.cmake @ONLY)

set(CDT_ROOT_DIR ${CMAKE_INSTALL_PREFIX})

configure_file(${CMAKE_SOURCE_DIR}/cmake/KoinosWasmToolchain.cmake.in ${CMAKE_BINARY_DIR}/cmake/KoinosWasmToolchain.cmake @ONLY)

set( INSTALL_KOINOS_TYPES ON )

