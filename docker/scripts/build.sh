#!/bin/bash

set -e
set -x

# copy sources in to project
cd /sources
find . -name \*.proto -exec cp {} /opt/project/types \;
find . -name \*.c     -exec cp {} /opt/project/src \;
find . -name \*.cpp   -exec cp {} /opt/project/src \;
find . -name \*.h     -exec cp {} /opt/project/src \;
find . -name \*.hpp   -exec cp {} /opt/project/src \;

# build contract
cd /opt/project
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=${KOINOS_CDT_ROOT}/cmake/koinos-wasm-toolchain.cmake -DCMAKE_BUILD_TYPE=Release ..
make contract

# copy build artifacts
cd src
cp contract.wasm /sources
cd ../types
cp types.pb /sources
