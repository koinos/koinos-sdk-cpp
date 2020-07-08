
add_custom_target(
   koinos-clang

   COMMAND make -C "${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/"
)
