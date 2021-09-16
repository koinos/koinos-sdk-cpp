set(Protobuf_DIR ${KOINOS_PROTOBUF_ROOT}/lib/cmake/protobuf)
include(${KOINOS_PROTOBUF_ROOT}/lib/cmake/protobuf/protobuf-config.cmake)
include(${KOINOS_PROTOBUF_ROOT}/lib/cmake/protobuf/protobuf-module.cmake)
include(${KOINOS_PROTOBUF_ROOT}/lib/cmake/protobuf/protobuf-options.cmake)
include(${KOINOS_PROTOBUF_ROOT}/lib/cmake/protobuf/protobuf-targets.cmake)

find_package(Protobuf 3.17.3.0 EXACT REQUIRED CONFIG)
if (Protobuf_FOUND)
    message(STATUS "Protobuf version : ${Protobuf_VERSION}")
    message(STATUS "Protobuf include path : ${Protobuf_INCLUDE_DIRS}")
    message(STATUS "Protobuf libraries : ${Protobuf_LIBRARIES}")
    message(STATUS "Protobuf compiler libraries : ${Protobuf_PROTOC_LIBRARIES}")
    message(STATUS "Protobuf lite libraries : ${Protobuf_LITE_LIBRARIES}")
else()
    message(WARNING "Protobuf package not found -> specify search path via PROTOBUF_ROOT variable")
endif()

###

function(koinos_generate_proto)
  include(CMakeParseArguments)

  set(_options APPEND_PATH)
  set(_singleargs LANGUAGE OUT_VAR EXPORT_MACRO PROTOC_OUT_DIR PLUGIN)
  if(COMMAND target_sources)
    list(APPEND _singleargs TARGET)
  endif()
  set(_multiargs PROTOS IMPORT_DIRS GENERATE_EXTENSIONS PROTOC_OPTIONS)

  cmake_parse_arguments(koinos_generate_proto "${_options}" "${_singleargs}" "${_multiargs}" "${ARGN}")

  if(NOT koinos_generate_proto_PROTOS AND NOT koinos_generate_proto_TARGET)
    message(SEND_ERROR "Error: koinos_generate_proto called without any targets or source files")
    return()
  endif()

  if(NOT koinos_generate_proto_OUT_VAR AND NOT koinos_generate_proto_TARGET)
    message(SEND_ERROR "Error: koinos_generate_proto called without a target or output variable")
    return()
  endif()

  if(NOT koinos_generate_proto_LANGUAGE)
    set(koinos_generate_proto_LANGUAGE eams)
  endif()
  string(TOLOWER ${koinos_generate_proto_LANGUAGE} koinos_generate_proto_LANGUAGE)

  if(NOT koinos_generate_proto_PROTOC_OUT_DIR)
    set(koinos_generate_proto_PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
  endif()

  if(koinos_generate_proto_EXPORT_MACRO AND koinos_generate_proto_LANGUAGE STREQUAL cpp)
    set(_dll_export_decl "dllexport_decl=${koinos_generate_proto_EXPORT_MACRO}:")
  endif()

  if(NOT koinos_generate_proto_PLUGIN)
    set(koinos_generate_proto_PLUGIN "protoc-gen-eams=${EAMS_DIR}/protoc-gen-eams")
  endif()

  if(koinos_generate_proto_PLUGIN)
      set(_plugin "--plugin=${koinos_generate_proto_PLUGIN}")
  endif()

  if(NOT koinos_generate_proto_GENERATE_EXTENSIONS)
    if(koinos_generate_proto_LANGUAGE STREQUAL cpp)
      set(koinos_generate_proto_GENERATE_EXTENSIONS .pb.h .pb.cc)
    elseif(koinos_generate_proto_LANGUAGE STREQUAL python)
      set(koinos_generate_proto_GENERATE_EXTENSIONS _pb2.py)
    elseif(koinos_generate_proto_LANGUAGE STREQUAL eams)
      set(koinos_generate_proto_GENERATE_EXTENSIONS .hpp .cpp)
    else()
      message(SEND_ERROR "Error: koinos_generate_proto given unknown Language ${LANGUAGE}, please provide a value for GENERATE_EXTENSIONS")
      return()
    endif()
  endif()

  if(koinos_generate_proto_TARGET)
    get_target_property(_source_list ${koinos_generate_proto_TARGET} SOURCES)
    foreach(_file ${_source_list})
      if(_file MATCHES "proto$")
        list(APPEND koinos_generate_proto_PROTOS ${_file})
      endif()
    endforeach()
  endif()

  if(NOT koinos_generate_proto_PROTOS)
    message(SEND_ERROR "Error: koinos_generate_proto could not find any .proto files")
    return()
  endif()

  if(koinos_generate_proto_APPEND_PATH)
    # Create an include path for each file specified
    foreach(_file ${koinos_generate_proto_PROTOS})
      get_filename_component(_abs_file ${_file} ABSOLUTE)
      get_filename_component(_abs_path ${_abs_file} PATH)
      list(FIND _protobuf_include_path ${_abs_path} _contains_already)
      if(${_contains_already} EQUAL -1)
          list(APPEND _protobuf_include_path -I ${_abs_path})
      endif()
    endforeach()
  endif()

  foreach(DIR ${koinos_generate_proto_IMPORT_DIRS})
    get_filename_component(ABS_PATH ${DIR} ABSOLUTE)
    list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
    if(${_contains_already} EQUAL -1)
        list(APPEND _protobuf_include_path -I ${ABS_PATH})
    endif()
  endforeach()

  if(NOT _protobuf_include_path)
    set(_protobuf_include_path -I ${CMAKE_CURRENT_SOURCE_DIR})
  endif()

  set(_generated_srcs_all)
  foreach(_proto ${koinos_generate_proto_PROTOS})
    get_filename_component(_abs_file ${_proto} ABSOLUTE)
    get_filename_component(_abs_dir ${_abs_file} DIRECTORY)

    get_filename_component(_file_full_name ${_proto} NAME)
    string(FIND "${_file_full_name}" "." _file_last_ext_pos REVERSE)
    string(SUBSTRING "${_file_full_name}" 0 ${_file_last_ext_pos} _basename)

    set(_suitable_include_found FALSE)
    foreach(DIR ${_protobuf_include_path})
      if(NOT DIR STREQUAL "-I")
        file(RELATIVE_PATH _rel_dir ${DIR} ${_abs_dir})
        string(FIND "${_rel_dir}" "../" _is_in_parent_folder)
        if (NOT ${_is_in_parent_folder} EQUAL 0)
          set(_suitable_include_found TRUE)
          break()
        endif()
      endif()
    endforeach()

    if(NOT _suitable_include_found)
      message(SEND_ERROR "Error: koinos_generate_proto could not find any correct proto include directory.")
      return()
    endif()

    set(_generated_srcs)
    foreach(_ext ${koinos_generate_proto_GENERATE_EXTENSIONS})
      list(APPEND _generated_srcs "${koinos_generate_proto_PROTOC_OUT_DIR}/${_rel_dir}/${_basename}${_ext}")
    endforeach()
    list(APPEND _generated_srcs_all ${_generated_srcs})

    if (WIN32)
      set(koinos_generate_proto_SCRIPT ${CMAKE_COMMAND} -E env "PATH=${KOINOS_PROTOBUF_ROOT}/bin;$ENV{PATH}" ${KOINOS_CDT_ROOT}/scripts/koinos_generate_proto.bat)
    else()
      set(koinos_generate_proto_SCRIPT ${CMAKE_COMMAND} -E env "PATH=${KOINOS_PROTOBUF_ROOT}/bin:$ENV{PATH}" ${KOINOS_CDT_ROOT}/scripts/koinos_generate_proto.sh)
    endif (WIN32)

    add_custom_command(
      OUTPUT ${_generated_srcs}
      COMMAND ${koinos_generate_proto_SCRIPT}
      ARGS ${koinos_generate_proto_PROTOC_OPTIONS} --${koinos_generate_proto_LANGUAGE}_out ${_dll_export_decl}${koinos_generate_proto_PROTOC_OUT_DIR} ${_plugin} ${_protobuf_include_path} ${_abs_file} --descriptor_set_out=${CMAKE_CURRENT_BINARY_DIR}/${koinos_generate_proto_TARGET}.pb
      DEPENDS ${_abs_file} protobuf::protoc
      WORKING_DIRECTORY ${KOINOS_EMBEDDED_PROTO_ROOT}
      COMMENT "Running ${koinos_generate_proto_LANGUAGE} protocol buffer compiler on ${_proto}. Custom options: ${koinos_generate_proto_PROTOC_OPTIONS}"
      VERBATIM )
  endforeach()

  set_source_files_properties(${_generated_srcs_all} PROPERTIES GENERATED TRUE)
  if(koinos_generate_proto_OUT_VAR)
    set(${koinos_generate_proto_OUT_VAR} ${_generated_srcs_all} PARENT_SCOPE)
  endif()
  if(koinos_generate_proto_TARGET)
    target_sources(${koinos_generate_proto_TARGET} PRIVATE ${_generated_srcs_all})
  endif()

endfunction()


