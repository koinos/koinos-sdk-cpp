#!/bin/bash
set -e
set -x

if [ "$1" != "-p" ]
  then
    echo "Please provide a path by using the '-p' flag followed by the desired installation path."
    exit 1
  else
    while getopts ':p:' OPTION; do
      case "$OPTION" in
        p)
          install_dir="$OPTARG"
          ;;
        "")
          echo "please choose a directory"
          ;;
        ?)
          echo "script usage: ./$(basename $0) -p path" >&2
          exit 1
          ;;
        *)
        echo "Invalid option: $OPTARG requires an argument" 1>&2
        ;;
      esac
    done
    shift "$(($OPTIND -1))"


    mkdir $install_dir
    tar xfv koinos-cdt.tar.gz -C $install_dir
    echo "Great success! Koinos CDT installed in the $install_dir directory"
fi