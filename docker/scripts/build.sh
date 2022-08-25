#!/bin/bash

# copy sources in to project
mkdir -p /tmp/project && cp -r /opt/koinos-sdk/cpp/project/* /tmp/project/
cd /src
find . -name \*.proto -exec cp {} /tmp/project/types \;
find . -name \*.c     -exec cp {} /tmp/project/src \;
find . -name \*.cpp   -exec cp {} /tmp/project/src \;
find . -name \*.h     -exec cp {} /tmp/project/src \;
find . -name \*.hpp   -exec cp {} /tmp/project/src \;

# set env vars
export KOINOS_WASI_SDK_ROOT=/opt/wasi-sdk
export KOINOS_PROTOBUF_ROOT=/opt/protobuf
export KOINOS_EMBEDDED_PROTO_ROOT=/opt/EmbeddedProto
export KOINOS_SDK_ROOT=/opt/koinos-sdk/cpp

# build contract
cd /tmp/project
mkdir build
cd build
/opt/cmake/bin/cmake -DCMAKE_TOOLCHAIN_FILE=${KOINOS_SDK_ROOT}/cmake/koinos-wasm-toolchain.cmake -DCMAKE_BUILD_TYPE=Release ..
make contract

# copy build artifacts
if [ $? -eq 0 ]; then
   mkdir /src/build

   USER=`stat -c "%u" /src/*.ts | head -n 1`
   GROUP=`stat -c "%g" /src/*.ts | head -n 1`

   cd src
   cp contract.wasm /src/build
   chown $USER:$GROUP /src/build/contract.wasm

   cd ../types
   if [ -e types.pb ]; then
      cp types.pb /src/build
      chown $USER:$GROUP /src/build/types.pb
   fi
fi

# cleanup
cd ~
rm -rf /tmp/project
