#include <koinos/system/system_calls.hpp>

namespace koinos::system {

types::thunks::prints_ret prints( const types::thunks::prints_args& args )
{
   auto arg_blob = koinos::pack::to_variable_blob( args );
   types::variable_blob ret_blob;
   ret_blob.resize( KOINOS_SYSTEM_MAX_RET_BUFFER );
   invoke_system_call( (uint32_t)types::system::system_call_id::prints, arg_blob.data(), arg_blob.size(), ret_blob.data(), ret_blob.size() );
   return koinos::pack::from_variable_blob< types::thunks::prints_ret >( ret_blob );
}

types::thunks::get_contract_args_ret get_contract_args( const types::thunks::get_contract_args_args& args )
{
   auto arg_blob = koinos::pack::to_variable_blob( args );
   types::variable_blob ret_blob;
   ret_blob.resize( KOINOS_SYSTEM_MAX_RET_BUFFER );
   invoke_system_call( (uint32_t)types::system::system_call_id::get_contract_args, arg_blob.data(), arg_blob.size(), ret_blob.data(), ret_blob.size() );
   return koinos::pack::from_variable_blob< types::thunks::get_contract_args_ret >( ret_blob );
}

} // koinos::system
