#!/bin/bash

usage="$(basename "$0") [-h] [-d dir] -- program to install the koinos contract development toolkit

where:
    -h  show this help text
    -d  the installation directory"

while getopts ':d:h' flag
do
   case "${flag}" in
      h) echo "$usage"
         exit
         ;;
      d) install_dir=${OPTARG};;
      :) printf "invalid option: -%s requires an argument\n" "$OPTARG" >&2
         echo "$usage" >&2
         exit 1
         ;;
      \?) printf "illegal option: -%s\n" "$OPTARG" >&2
         echo "$usage" >&2
         exit 1
         ;;
   esac
done

mkdir -p $install_dir

tar xfv build/koinos-cdt.tar.gz -C $install_dir

echo "Koinos CDT installed to $install_dir"

