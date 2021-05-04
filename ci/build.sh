#!/bin/bash

set -e
set -x

export KOINOS_WASI_SDK_ROOT=/opt/wasi-sdk-12.0
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$HOME/opt ..
cmake --build . --config Release --parallel 3

