#!/bin/bash

set -e
set -x

# copy sources in to project
cd /sources
cp *.proto /opt/project/types
cp *.c     /opt/project/src
cp *.cpp   /opt/project/src
cp *.h     /opt/project/src
cp *.hpp   /opt/project/src

# build contract
cp -R /opt/project /tmp/project
cp /tmp/project
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=${KOINOS_CDT_ROOT}/cmake/koinos-wasm-toolchain.cmake -DCMAKE_BUILD_TYPE=Release ..
make -j

# copy build artifacts
cd src
cp contract.wasm /sources
cd ../types
cp types.pb /sources

# cleanup project source
cd ~
rm -rf /tmp/project
