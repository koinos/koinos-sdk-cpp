#!/bin/bash

set -e
set -x

curl -L https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-12/wasi-sdk-12.0-linux.tar.gz -o wasi-sdk-12.0.tar.gz

mkdir -p $HOME/opt
tar -xvzf wasi-sdk-12.0.tar.gz -C $HOME/opt

pip3 install --user dataclasses_json Jinja2 importlib_resources pluginbase gitpython

