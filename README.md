
## Components

- `koinos_api_c` : C library for invoking Koinos API syscalls with C syntax
- `koinos_api_cpp` : C++ library for invoking Koinos API syscall with C++ syntax
- `koinos_wasi_api` : C library for translating WASI syscalls to Koinos API syscalls
- `koinos-types` : C++ serialization library for Koinos
- `libc++` : Full C++ standard library for developing Koins smart contracts
- `boost` : Header only Boost libraries

## Installation

### Build from source

You can build the Koinos CDT from source. This builds a full llvm toolchain targetting WASM and Koinos. As such, it takes some time.

You will want to install the CDT. We'll refer to your installation location as `CDT_INSTALL_PATH`.

```
git clone --recursive git@github.com:koinos/koinos-cdt.git`
cd koinos-cdt
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTAL_PREFIX=$CDT_INSTALL_PATH ..
make -j
make install
```

Congrats, you now have the Koinos-CDT installed. LLVM executables can be found in `$CDT_INSTALL_PATH/wasi-sdk/bin`.
All other headers can be found in `$CDT_INSTALL_PATH/include`.

### Script Installation

Download the packaged CDT for your system from the latest releaese on GitHub.

Extract the archive to your installation directory.

`mkdir -p $CDT_INSTALL_PATH && tar xvf koinos-cdt.tar.gz -C $CDT_INSTALL_PATH`

## Using the CDT

This simple scipt can compiler a single source contract.

```
#!/bin/bash

set -e
set -x

"$CDT_INSTALL_PATH/wasi-sdk/bin/clang++" \
   \
   -v \
   --sysroot="$CDT_INSTALL_PATH/wasi-sdk/share/wasi-sysroot" \
   --target=wasm32-wasi \
   -L$CDT_INSTALL_PATH/lib \
   -I$CDT_INSTALL_PATH/include \
   -lkoinos_api \
   -lkoinos_api_cpp \
   -lkoinos_wasi_api \
   -Wl,--allow-undefined \
   \
   -std=c++17 \
   \
   -o $2 \
   $1
```

Invocation is as simple as:

`build_koinos_contract.sh my_contract.cpp my_contract.wasm`
