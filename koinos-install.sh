#!/bin/bash

read -p "Enter desired installation directory name: " install_dir

mkdir $install_dir

tar xfv koinos-cdt.tar.gz -C $install_dir

echo "\n"
echo "Great success! Koinos CDT installed in the $install_dir directory"