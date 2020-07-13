#include <koinos/pack/rt/binary.hpp>
#include <koinos/pack/classes.hpp>
#include <koinos/pack/system_call_ids.hpp>

#define KOINOS_SYSTEM_MAX_RET_BUFFER 1 << 20

extern "C" void invoke_system_call( uint32_t sid, char* ret_ptr, uint32_t ret_len, char* arg_ptr, uint32_t arg_len );

namespace koinos::system {

types::thunks::prints_ret prints( const types::thunks::prints_args& args );

types::thunks::get_contract_args_ret get_contract_args( const types::thunks::get_contract_args_args& args );


} // koinos::system
