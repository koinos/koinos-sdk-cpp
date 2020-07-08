
add_custom_target(
   koinos_wasi_sdk

   DEPENDS
      ${CMAKE_C_COMPILER}
      ${CMAKE_CXX_COMPILER}
      ${CMAKE_AR}
      ${CMAKE_LINKER}
      ${CMAKE_NM}
      ${CMAKE_OBJCOPY}
      ${CMAKE_OBJDUMP}
      ${CMAKE_RANLIB}
      ${CMAKE_STRIP}
)

add_custom_command(
   OUTPUT
      ${CMAKE_C_COMPILER}
      ${CMAKE_CXX_COMPILER}
      ${CMAKE_AR}
      ${CMAKE_LINKER}
      ${CMAKE_NM}
      ${CMAKE_OBJCOPY}
      ${CMAKE_OBJDUMP}
      ${CMAKE_RANLIB}
      ${CMAKE_STRIP}

   COMMAND make -C ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk
)
