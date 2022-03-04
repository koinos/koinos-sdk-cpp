#!/bin/bash
set -e
set -x

rm -rf host/koinos-wasi-sdk/build

mkdir build/

cd build

mkdir koinos-sdk

cmake -DCMAKE_INSTALL_PREFIX=`pwd`/koinos-sdk ..

make

make install

tar -czvf koinos-sdk.tar.gz koinos-sdk
