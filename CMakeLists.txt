
cmake_minimum_required (VERSION 3.10.2)

project( koinos-sdk )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION_FULL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

include( KoinosBoostHeaders )
include( KoinosConfigureToolchain )
include( KoinosLibraries )
include( KoinosProtoInstall )
