configure_file(${CMAKE_SOURCE_DIR}/cmake/KoinosWasmToolchain.cmake.in ${CMAKE_BINARY_DIR}/cmake/koinos-wasm-toolchain.cmake @ONLY)

install(FILES ${CMAKE_BINARY_DIR}/cmake/koinos-wasm-toolchain.cmake DESTINATION cmake)
