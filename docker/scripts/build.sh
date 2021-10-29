#!/bin/bash

set -e

# copy sources in to project
cp -R /opt/project /tmp/project
cd /src
find . -name \*.proto -exec cp {} /tmp/project/types \;
find . -name \*.c     -exec cp {} /tmp/project/src \;
find . -name \*.cpp   -exec cp {} /tmp/project/src \;
find . -name \*.h     -exec cp {} /tmp/project/src \;
find . -name \*.hpp   -exec cp {} /tmp/project/src \;

# build contract
cd /tmp/project
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=${KOINOS_CDT_ROOT}/cmake/koinos-wasm-toolchain.cmake -DCMAKE_BUILD_TYPE=Release ..
make contract

# copy build artifacts
cd src
cp contract.wasm /src
cd ../types
cp types.pb /src

# cleanup
cd ~
rm -rf /tmp/project
