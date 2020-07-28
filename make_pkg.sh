#!/bin/bash

rm -rf host/koinos-wasi-sdk/build

mkdir build/

cd build

mkdir koinos-cdt

cmake -DCMAKE_INSTALL_PREFIX=`pwd`/koinos-cdt ..

make

make install

tar -czvf koinos-cdt.tar.gz koinos-cdt



