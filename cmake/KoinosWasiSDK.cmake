include( ExternalProject )

set( KOINOS_WASI_SDK_INSTALL_PATH ${CMAKE_BINARY_DIR}/install/ )
set( KOINOS_WASI_SDK_BUILD_PATH ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/build/install )

if( NOT KOINOS_WASI_SDK_PATH )

   add_custom_target(
      koinos_wasi_sdk

      DEPENDS ${CMAKE_BINARY_DIR}/koinos_wasi_sdk.BUILT
   )

   add_custom_command(
      COMMAND make -C ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk &&
         mv ${KOINOS_WASI_SDK_BUILD_PATH}/* ${KOINOS_WASI_SDK_INSTALL_PATH} &&
         touch ${CMAKE_BINARY_DIR}/koinos_wasi_sdk.BUILT

      OUTPUT ${CMAKE_BINARY_DIR}/koinos_wasi_sdk.BUILT
   )

else()

   add_custom_target( koinos_wasi_sdk )

endif( NOT KOINOS_WASI_SDK_PATH )
