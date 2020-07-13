file(GLOB HEADERS "include/koinos/system/*.hpp")
add_library( koinos_api_cpp
             koinos_api_cpp.cpp
             system_calls.cpp
             ${HEADERS} )
target_include_directories( koinos_api_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_link_libraries( koinos_api_cpp koinos_types )

install( TARGETS
   koinos_api_cpp

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
install( FILES ${HEADERS} DESTINATION "include/koinos/system" )
