#!/bin/bash
echo "Unless explicitly specified provided path will be relative to current directory"
read -p "Enter desired installation directory name: " install_dir

mkdir $install_dir

tar xfv koinos-cdt.tar.gz -C $install_dir

echo -e "\nGreat success! Koinos CDT installed in the $install_dir directory\n"