include(ExternalProject)

find_package(Boost 1.57 REQUIRED)

ExternalProject_Add(
  KoinosWasmLibraries
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/libraries"
  BINARY_DIR "${CMAKE_BINARY_DIR}/libraries"
  CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_BINARY_DIR}/lib/cmake/koinos-cdt/KoinosWasmToolchain.cmake -DBoost_INCLUDE_DIR=${Boost_INCLUDE_DIR} -DBUILD_TYPES_TESTS=OFF
  UPDATE_COMMAND ""
  PATCH_COMMAND  ""
  TEST_COMMAND   ""
  INSTALL_COMMAND ""
  BUILD_ALWAYS 1
  DEPENDS koinos_wasi_sdk
)
