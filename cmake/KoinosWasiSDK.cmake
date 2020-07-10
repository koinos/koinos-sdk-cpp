include( ExternalProject )

if( NOT KOINOS_WASI_SDK_PATH )

   add_custom_target(
      koinos_wasi_sdk

      COMMAND mv -f ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/build/install/* ${CMAKE_BINARY_DIR}/install/

      DEPENDS ${CMAKE_BUILD_DIRECTORY}/koinos_wasi_sdk.BUILT
   )

   add_custom_command(
      COMMAND make -C ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk

      OUTPUT ${CMAKE_BUILD_DIRECTORY}/koinos_wasi_sdk.BUILT
   )

else()

   add_custom_target( koinos_wasi_sdk )

endif( NOT KOINOS_WASI_SDK_PATH )
