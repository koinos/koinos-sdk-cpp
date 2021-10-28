file(GLOB PROTO_FILES *.proto)

add_library(types INTERFACE ${PROTO_FILES})

target_include_directories(types INTERFACE ${CMAKE_CURRENT_BINARY_DIR})

koinos_generate_proto(TARGET types)
