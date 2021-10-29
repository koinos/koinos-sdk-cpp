install(PROGRAMS ${PROJECT_SOURCE_DIR}/scripts/koinos_generate_proto.sh DESTINATION scripts)
install(PROGRAMS ${PROJECT_SOURCE_DIR}/scripts/koinos_generate_proto.bat DESTINATION scripts)
install(FILES ${PROJECT_SOURCE_DIR}/cmake/KoinosProto.cmake DESTINATION cmake)
install(
   DIRECTORY ${PROJECT_SOURCE_DIR}/proto/koinos
   DESTINATION proto
   FILES_MATCHING PATTERN "*.proto" )
