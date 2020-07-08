
cmake_minimum_required (VERSION 3.10.2)

project( koinos_system )

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

if( NOT KOINOS_WASI_SDK_PATH )
   set(KOINOS_WASI_SDK_PATH /opt/koinos-wasi-sdk)
endif( NOT KOINOS_WASI_SDK_PATH )

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

add_subdirectory(libraries)
