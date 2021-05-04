#!/bin/bash

set -e
set -x

sudo curl -L https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-12/wasi-sdk-12.0-linux.tar.gz -o wasi-sdk-12.tar.gz
sudo tar -xvzf wasi-sdk-12.tar.gz -C /

