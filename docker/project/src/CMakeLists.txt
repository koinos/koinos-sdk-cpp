file(GLOB SOURCES *.c *.cpp *.h *.hpp)

add_executable(contract SOURCES)
target_link_libraries(contract types koinos_proto_embedded koinos_api koinos_api_cpp koinos_wasi_api c c++ c++abi clang_rt.builtins-wasm32)
