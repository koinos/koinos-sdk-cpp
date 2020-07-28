include(ExternalProject)

message(STATUS "About to build boost into ${CDT_ROOT_DIR}")

add_custom_command(
   COMMAND cd ${CMAKE_SOURCE_DIR}/libraries/boost &&
      ./bootstrap.sh &&
      ./b2 headers &&
      mv ${CMAKE_SOURCE_DIR}/libraries/boost/boost ${CDT_ROOT_DIR}/include

   OUTPUT ${CDT_ROOT_DIR}/include/boost
)

ExternalProject_Add(
   KoinosWasmLibraries
   SOURCE_DIR "${CMAKE_SOURCE_DIR}/libraries"
   BINARY_DIR "${CMAKE_BINARY_DIR}/libraries"
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_BINARY_DIR}/lib/cmake/koinos-cdt/KoinosWasmToolchain.cmake -DBoost_INCLUDE_DIR=${CDT_ROOT_DIR}/include -DBUILD_TYPES_TESTS=OFF -DINSTALL_KOINOS_TYPES_HEADERS=ON -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
   UPDATE_COMMAND ""
   PATCH_COMMAND  ""
   TEST_COMMAND   ""
   BUILD_ALWAYS 1
   DEPENDS koinos_wasi_sdk
)
