file(GLOB HEADERS "include/koinos/system/*.h")
add_library( koinos_api
             koinos_api.c
             ${HEADERS} )
target_include_directories( koinos_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

install( TARGETS
   koinos_api

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
install( FILES ${HEADERS} DESTINATION "include/koinos/system" )
