#!/bin/bash

mkdir build/

cd build

mkdir koinos-cdt

cmake -DCMAKE_INSTALL_PREFIX=`pwd`/koinos-cdt ..

make 

make install

tar -czvf koinos-cdt.tar.gz build/koinos-cdt



