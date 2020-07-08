file(GLOB HEADERS "include/koinos/wasi_api/*.h")
add_library( koinos_wasi_api
             wasi_api.c
             ${HEADERS} )
target_link_libraries( koinos_wasi_api koinos_api )
# No target_include_directories for now
# target_include_directories( koinos_wasi_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install( TARGETS
   koinos_wasi_api

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
install( FILES ${HEADERS} DESTINATION "include/koinos/wasi_api" )
