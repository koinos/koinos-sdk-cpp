
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

set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "wasm")

include( KoinosWasiSDK )

set(CMAKE_SYSROOT "${KOINOS_WASI_SDK_PATH}/share/wasi-sysroot")
# set(CMAKE_STAGING_PREFIX /home/devel/stage)

set(CMAKE_C_COMPILER   "${KOINOS_WASI_SDK_PATH}/bin/clang")
set(CMAKE_CXX_COMPILER "${KOINOS_WASI_SDK_PATH}/bin/clang++")
set(CMAKE_AR           "${KOINOS_WASI_SDK_PATH}/bin/ar")
set(CMAKE_LINKER       "${KOINOS_WASI_SDK_PATH}/bin/ld")
set(CMAKE_NM           "${KOINOS_WASI_SDK_PATH}/bin/nm")
set(CMAKE_OBJCOPY      "${KOINOS_WASI_SDK_PATH}/bin/objcopy")
set(CMAKE_OBJDUMP      "${KOINOS_WASI_SDK_PATH}/bin/objdump")
set(CMAKE_RANLIB       "${KOINOS_WASI_SDK_PATH}/bin/ranlib")
set(CMAKE_STRIP        "${KOINOS_WASI_SDK_PATH}/bin/strip")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

if(${CMAKE_GENERATOR} MATCHES "Xcode")
  set(CMAKE_XCODE_GENERATE_SCHEME YES)
endif()

### Configure the KoinosWasmToolchain.cmakes
set(CDT_ROOT_DIR ${CMAKE_BINARY_DIR})

configure_file(${CMAKE_SOURCE_DIR}/cmake/KoinosWasmToolchain.cmake.in ${CMAKE_BINARY_DIR}/lib/cmake/koinos-cdt/KoinosWasmToolchain.cmake @ONLY)

set(CDT_ROOT_DIR ${CMAKE_INSTALL_PREFIX})

configure_file(${CMAKE_SOURCE_DIR}/cmake/KoinosWasmToolchain.cmake.in ${CMAKE_BINARY_DIR}/cmake/KoinosWasmToolchain.cmake @ONLY)

set( INSTALL_KOINOS_TYPES ON )

add_subdirectory( libraries )
