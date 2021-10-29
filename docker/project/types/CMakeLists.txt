file(GLOB PROTO_FILES *.proto)

add_library(types INTERFACE ${PROTO_FILES})

target_include_directories(types INTERFACE ${CMAKE_CURRENT_BINARY_DIR})

if( NOT ${PROTO_FILES} EQUAL "" )
   koinos_generate_proto(TARGET types)
endif()
