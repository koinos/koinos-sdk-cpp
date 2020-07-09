include( ExternalProject )

if( NOT KOINOS_WASI_SDK_PATH )

   if( NOT PREFIX )
      set( PREFIX "/opt/wasi-sdk" )
   endif()

   set( ROOT_DIR ${CMAKE_BINARY_DIR}/host/koinos-wasi-sdk )
   set( LLVM_PROJ_DIR ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/src/llvm_project )
   set( BUILD_PREFIX ${ROOT_DIR}${PREFIX} )

   execute_process( COMMAND "${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/llvm_version.sh ${LLVM_PROJ_DIR}"
      OUTPUT_VARIABLE CLANG_VERSION )

   set( DEBUG_PREFIX_MAP -fdebug-prefix-map=${ROOT_DIR}=wasisdk://v${VERSION})

   add_custom_target( llvm_config
      DEPENDS
         ${BUILD_PREFIX}/share/misc/config.sub
         ${BUILD_PREFIX}/share/misc/config.guess
         ${BUILD_PREFIX}/share/cmake/wasi-sdk.cmake
   )

   add_custom_command(
      COMMAND mkdir -p ${BUILD_PREFIX}/share/misc
      COMMAND cp ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/src/config/config.sub ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/src/config/config.guess ${BUILD_PREFIX}/share/misc
      COMMAND mkdir -p ${BUILD_PREFIX}/share/cmake
      COMMAND cp ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/wasi-sdk.cmake ${BUILD_PREFIX}/share/cmake

      OUTPUT
         ${BUILD_PREFIX}/share/misc/config.sub
         ${BUILD_PREFIX}/share/misc/config.guess
         ${BUILD_PREFIX}/share/cmake/wasi-sdk.cmake
   )

   ExternalProject_Add(
      llvm
      CMAKE_ARGS -DCMAKE_BUILD_TYPE=MinSizeRel
                 -DLLVM_TARGETS_TO_BUILD=WebAssembly
                 -DLLVM_DEFAULT_TARGET_TRIPLE=wasm32-wasi
                 -DLLVM_ENABLE_PROJECTS="lld;clang;clang-tools-extra"
                 -DDEFAULT_SYSROOT=${PREFIX}/share/wasi-sysroot
                 -DLLVM_INSTALL_BINUTILS_SYMLINKS=TRUE
                 -DCMAKE_INSTALL_PREFIX="$CMAKE_BINARY_DIR}/install/${prefix}"

      SOURCE_DIR ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/src/llvm-project/llvm
      BINARY_DIR ${CMAKE_BINARY_DIR}/llvm-project/llvm
      BUILD_COMMAND   "cmake --build . --install"
      UPDATE_COMMAND  ""
      PATCH_COMMAND   ""
      TEST_COMMAND    ""
      INSTALL_COMMAND ""
      BUILD_ALWAYS 1
   )

   # Build wasi-libc

   add_custom_target( wasi_libc )
   add_dependencies( wasi_libc llvm )

   message(STATUS "${COMPILER_RT_DEFAULT_TARGET_TRIPLE}")
   message(STATUS "${CMAKE_C_COMPILER}")

   ExternalProject_Add(
      compiler_rt
      CMAKE_ARGS -DCMAKE_BUILD_TYPE=RelWithDebInfo
                 -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/wasi-sdk.cmake
                 -DCOMPILER_RT_BAREMETAL_BUILD=On
                 -DCOMPILER_RT_BUILD_XRAY=OFF
                 -DCOMPILER_RT_INCLUDE_TESTS=OFF
                 -DCOMPILER_RT_HAS_FPIC_FLAG=OFF
                 -DCOMPILER_RT_ENABLE_IOS=OFF
                 -DCOMPILER_RT_DEFAULT_TARGET_ONLY=On
                 -DWASI_SDK_PREFIX=${BUILD_PREFIX}
                 -DCMAKE_C_FLAGS="-O1 ${DEBUG_PREFIX_MAP}"
                 -DLLVM_CONFIG_PATH=${CMAKE_BINARY_DIR}/host/koinos-wasi-sdk/src/llvm-project/llvm/bin/llvm-config
                 -DCOMPILER_RT_OS_DIR=wasi
                 -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
                 -DCMAKE_INSTALL_PREFIX="$CMAKE_BINARY_DIR}/install/${prefix}"

      DEPENDS llvm llvm_config

      SOURCE_DIR ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/src/llvm-project/compiler-rt
      BINARY_DIR ${CMAKE_BINARY_DIR}/llvm-project/compiler-rt
      BUILD_COMMAND   "cmake --build . --install"
      UPDATE_COMMAND  ""
      PATCH_COMMAND   ""
      TEST_COMMAND    ""
      INSTALL_COMMAND ""
      BUILD_ALWAYS 1
   )

   ExternalProject_Add(
      libcxx
      CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/wasi-sdk.cmake
                 -DCMAKE_STAGING_PREFIX=${PREFIX}/share/wasi-sysroot
                 -DLLVM_CONFIG_PATH=${CMAKE_BINARY_DIR}/host/koinos-wasi-sdk/src/llvm-project/llvm/bin/llvm-config
                 -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
                 -DLIBCXX_ENABLE_THREADS:BOOL=OFF
                 -DLIBCXX_HAS_PTHREAD_API:BOOL=OFF
                 -DLIBCXX_HAS_EXTERNAL_THREAD_API:BOOL=OFF
                 -DLIBCXX_BUILD_EXTERNAL_THREAD_LIBRARY:BOOL=OFF
                 -DLIBCXX_HAS_WIN32_THREAD_API:BOOL=OFF
                 -DCMAKE_BUILD_TYPE=RelWithDebugInfo
                 -DLIBCXX_ENABLE_SHARED:BOOL=OFF
                 -DLIBCXX_ENABLE_EXPERIMENTAL_LIBRARY:BOOL=OFF
                 -DLIBCXX_ENABLE_EXCEPTIONS:BOOL=OFF
                 -DLIBCXX_ENABLE_FILESYSTEM:BOOL=OFF
                 -DLIBCXX_CXX_ABI=libcxxabi
                 -DLIBCXX_CXX_ABI_INCLUDE_PATHS=${LLVM_PROJ_DIR}/libcxxabi/include
                 -DLIBCXX_HAS_MUSL_LIBC:BOOL=ON
                 -DLIBCXX_ABI_VERSION=2
                 -DWASI_SDK_PREFIX=${BUILD_PREFIX}
                 --debug-trycompile
                 -DCMAKE_C_FLAGS="${DEBUG_PREFIX_MAP}"
                 -DCMAKE_CXX_FLAGS="${DEBUG_PREFIX_MAP}"
                 -DLIBCXX_LIBDIR_SUFFIX=/wasm32-wasi
                 -DCMAKE_INSTALL_PREFIX="$CMAKE_BINARY_DIR}/install/${prefix}"

      DEPENDS llvm compiler_rt wasi_libc

      SOURCE_DIR ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/src/llvm-project/libcxx
      BINARY_DIR ${CMAKE_BINARY_DIR}/llvm-project/libcxx
      BUILD_COMMAND   "cmake --build . --install"
      UPDATE_COMMAND  ""
      PATCH_COMMAND   ""
      TEST_COMMAND    ""
      INSTALL_COMMAND ""
      BUILD_ALWAYS 1
   )

   ExternalProject_Add(
      libcxxabi
      CMAKE_ARGS -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
                 -DCMAKE_CXX_COMPILER_WORKS=ON
                 -DCMAKE_C_COMPILER_WORKS=ON
                 -DLIBCXXABI_ENABLE_EXCEPTIONS:BOOL=OFF
                 -DLIBCXXABI_ENABLE_SHARED:BOOL=OFF
                 -DLIBCXXABI_SILENT_TERMINATE:BOOL=ON
                 -DLIBCXXABI_ENABLE_THREADS:BOOL=OFF
                 -DLIBCXXABI_HAS_PTHREAD_API:BOOL=OFF
                 -DLIBCXXABI_HAS_EXTERNAL_THREAD_API:BOOL=OFF
                 -DLIBCXXABI_BUILD_EXTERNAL_THREAD_LIBRARY:BOOL=OFF
                 -DLIBCXXABI_HAS_WIN32_THREAD_API:BOOL=OFF
                 -DLIBCXXABI_ENABLE_PIC:BOOL=OFF
                 -DCXX_SUPPORTS_CXX11=ON
                 -DLLVM_COMPILER_CHECKED=ON
                 -DCMAKE_BUILD_TYPE=RelWithDebugInfo
                 -DLIBCXXABI_LIBCXX_PATH=${LLVM_PROJ_DIR}/libcxx
                 -DLIBCXXABI_LIBCXX_INCLUDES=${BUILD_PREFIX}/share/wasi-sysroot/include/c++/v1
                 -DLLVM_CONFIG_PATH=${CMAKE_BINARY_DIR}/host/koinos-wasi-sdk/src/llvm-project/llvm/bin/llvm-config
                 -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/wasi-sdk.cmake
                 -DCMAKE_STAGING_PREFIX=${PREFIX}/share/wasi-sysroot
                 -DWASI_SDK_PREFIX=${BUILD_PREFIX}
                 -DUNIX:BOOL=ON
                 --debug-trycompile
                 -DCMAKE_C_FLAGS="${DEBUG_PREFIX_MAP}"
                 -DCMAKE_CXX_FLAGS="${DEBUG_PREFIX_MAP}"
                 -DLIBCXXABI_LIBDIR_SUFFIX=$(ESCAPE_SLASH)/wasm32-wasi
                 -DCMAKE_INSTALL_PREFIX="$CMAKE_BINARY_DIR}/install/${prefix}"

      DEPENDS llvm libcxx

      SOURCE_DIR ${CMAKE_SOURCE_DIR}/host/koinos-wasi-sdk/src/llvm-project/libcxxabi
      BINARY_DIR ${CMAKE_BINARY_DIR}/host/koinos-wasi-sdk/src/llvm-project/libcxxabi
      BUILD_COMMAND   "cmake --build . --install"
      UPDATE_COMMAND  ""
      PATCH_COMMAND   ""
      TEST_COMMAND    ""
      INSTALL_COMMAND ""
      BUILD_ALWAYS 1
   )

   add_custom_target( koinos_wasi_sdk )
   add_dependencies( koinos_wasi_sdk llvm compiler_rt libcxx libcxxabi )

else()

   add_custom_target( koinos_wasi_sdk )

endif( NOT KOINOS_WASI_SDK_PATH )
