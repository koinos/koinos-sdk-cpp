
Components:

- `koinos_api` : C library for invoking Koinos API syscalls with C syntax
- `koinos_wasi_api` : C library for translating WASI syscalls to Koinos API syscalls

Usage:

If you have `koinos-wasi-sdk` installed in `/opt/koinos-wasi-sdk`, then it should Just Work.

If you have `koinos-wasi-sdk` installed somewhere else, you can override the location like this:

```
cmake -DKOINOS_WASI_SDK_PATH=/path/to/koinos-wasi-sdk/build/install/opt/koinos-wasi-sdk ..
make
```
