include(ExternalProject)

ExternalProject_Add(
  KoinosWasmLibraries
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/libraries"
  BINARY_DIR "${CMAKE_BINARY_DIR}/libraries"
  CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_BINARY_DIR}/lib/cmake/koinos-cdt/KoinosWasmToolchain.cmake
  UPDATE_COMMAND ""
  PATCH_COMMAND  ""
  TEST_COMMAND   ""
  INSTALL_COMMAND ""
  BUILD_ALWAYS 1
  DEPENDS koinos_wasi_sdk
)

