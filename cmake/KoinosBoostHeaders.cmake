add_custom_target(
   boost_headers

   DEPENDS ${CMAKE_BINARY_DIR}/boost_headers.BUILT
)

add_custom_command(
   COMMAND cd ${CMAKE_SOURCE_DIR}/host/boost &&
      ./bootstrap.sh --prefix=${CMAKE_BINARY_DIR} &&
      ./b2 install --build-dir=${CMAKE_BINARY_DIR}/boost --with-headers &&
      touch ${CMAKE_BINARY_DIR}/boost_headers.BUILT

   OUTPUT ${CMAKE_BINARY_DIR}/boost_headers.BUILT
)

install( DIRECTORY ${CMAKE_BINARY_DIR}/include/ DESTINATION include )
