
## Components

- `koinos_api_c` : C library for invoking Koinos API syscalls with C syntax
- `koinos_api_cpp` : C++ library for invoking Koinos API syscall with C++ syntax
- `koinos_wasi_api` : C library for translating WASI syscalls to Koinos API syscalls
- `koinos-types` : C++ serialization library for Koinos
- `boost` : Header only Boost libraries

## Installation

You first need to download wasi-sdk. We recommend the pre-compiled release for your system. Building contracts
has been tested on wasi sdk 12.0. Release binaries can be found on their git repo. https://github.com/WebAssembly/wasi-sdk/releases/tag/wasi-sdk-12

Download and extract the wasi sdk to a location of your choosing. We recommend `$HOME/opt/wasi-sdk`. Save this
location in an env variable, `KOINOS_WASI_SDK_ROOT`.

Set `KOINOS_CDT_ROOT` to the location you want to install the CDT. We recommend `$HOME/opt/koinos-cdt`.

The CDT builds using cmake.

To build and install run the following commands:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$KOINOS_CDT_ROOT ..
make -j install
```

## Using the CDT

You can now use the CDT to build C++ smart contracts using the cmake toolchain file.

Create your cmake project like normal. You will need to set your `target_link_libraries` to `koinos_api koinos_api_cpp koinos_wasi_api c c++ c++abi clang_rt.builtins-wasm32`.

Invoke your cmake project with the following command:
`cmake -DCMAKE_TOOLCHAIN_FILE=${KOINOS_CDT_ROOT}/cmake/koinos-wasm-toolchain.cmake -DCMAKE_BUILD_TYPE=Release ..`

You will have `.wasm` binaries in your build directory which will be valid Koinos smart contracts, ready to upload to Koinos.
