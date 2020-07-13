
cmake_minimum_required (VERSION 3.10.2)

project( koinos-cdt )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)
set(VERSION_FULL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(KOINOS_CDT_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/koins-cdt)
set(INSTALL_KOINOS_TYPES ON)

include( KoinosWasiSDK )
include( KoinosConfigureToolchain )
include( KoinosLibraries )

