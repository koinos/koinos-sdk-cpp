include( ExternalProject )

set( KOINOS_WASI_SDK_INSTALL_PATH ${CMAKE_BINARY_DIR}/install )
set( KOINOS_WASI_SDK_BUILD_PATH ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/build )

if( NOT KOINOS_WASI_SDK_PATH )

   add_custom_target(
      koinos_wasi_sdk

      DEPENDS ${CMAKE_BINARY_DIR}/koinos_wasi_sdk.BUILT
   )

   add_custom_command(
      COMMAND make -C ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk VERBOSE=1 &&
         mv ${KOINOS_WASI_SDK_BUILD_PATH}/install/* ${KOINOS_WASI_SDK_INSTALL_PATH}/ &&
         rm -rf ${KOINOS_WASI_SDK_BUILD_PATH} &&
         touch ${CMAKE_BINARY_DIR}/koinos_wasi_sdk.BUILT

      OUTPUT ${CMAKE_BINARY_DIR}/koinos_wasi_sdk.BUILT
   )

   install( DIRECTORY ${KOINOS_WASI_SDK_INSTALL_PATH}/wasi-sdk/ DESTINATION wasi-sdk )

   set( KOINOS_WASI_SDK_PATH ${KOINOS_WASI_SDK_INSTALL_PATH}/wasi-sdk )

else()

   add_custom_target( koinos_wasi_sdk )

endif( NOT KOINOS_WASI_SDK_PATH )
