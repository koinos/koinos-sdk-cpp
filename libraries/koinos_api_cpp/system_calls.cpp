#include <koinos/system/system_calls.hpp>

extern "C" void invoke_system_call( uint32_t sid, char* ret_ptr, uint32_t ret_len, char* arg_ptr, uint32_t arg_len );

namespace koinos::system {

using namespace koinos::types;
using namespace koinos::types::system;
using namespace koinos::types::thunks;

namespace detail {
   static variable_blob return_buf( KOINOS_SYSTEM_MAX_RET_BUFFER );
}

void print( const std::string& s )
{
   auto args = pack::to_variable_blob( prints_args{ .message = s } );

   invoke_system_call(
      (uint32_t)system_call_id::prints,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );
}

uint32_t get_contract_args_size()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_contract_args_size,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );

   return pack::from_variable_blob< uint32_t >( detail::return_buf );
}

variable_blob get_contract_args()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_contract_args,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );

   return pack::from_variable_blob< get_contract_args_ret >( detail::return_buf );
}

void set_contract_return( const variable_blob& ret )
{
   auto args = pack::to_variable_blob(
      set_contract_return_args
      {
         .ret = ret
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::set_contract_return,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );
}

bool verify_block_header( const fixed_blob<65>& sig, const multihash_type& digest )
{
   auto args = pack::to_variable_blob( verify_block_header_args{ .sig = sig, .digest = digest } );

   invoke_system_call(
      (uint32_t)system_call_id::verify_block_header,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );

   return pack::from_variable_blob< bool >( detail::return_buf );
}

void apply_block( const protocol::active_block_data& b )
{
   auto args = pack::to_variable_blob( apply_block_args{ .block = b } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_block,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );
}

void apply_transaction( const protocol::transaction_type& t )
{
   auto args = pack::to_variable_blob( apply_transaction_args{ .trx = t } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_transaction,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );
}

void apply_reserved_operation( const protocol::reserved_operation& o )
{
   auto args = pack::to_variable_blob( apply_reserved_operation_args{ .op = o } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_reserved_operation,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );
}

void apply_upload_contract_operation( const protocol::create_system_contract_operation& o )
{
   auto args = pack::to_variable_blob( apply_upload_contract_operation_args{ .op = o } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_upload_contract_operation,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );
}

void apply_execute_contract_operation( const protocol::contract_call_operation& o )
{
   auto args = pack::to_variable_blob( apply_execute_contract_operation_args{ .op = o } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_execute_contract_operation,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );
}

void apply_set_system_call_operation( const protocol::set_system_call_operation& o )
{
   auto args = pack::to_variable_blob( apply_set_system_call_operation_args{ .op = o } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_set_system_call_operation,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );
}

bool db_put_object( const uint256& space, const uint256& key, const variable_blob& obj )
{
   auto args = pack::to_variable_blob(
      db_put_object_args
      {
         .space = space,
         .key = key,
         .obj = obj
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::db_put_object,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );

   return pack::from_variable_blob< bool >( detail::return_buf );
}

variable_blob db_get_object( const uint256& space, const uint256& key, int32_t object_size_hint )
{
   auto args = pack::to_variable_blob(
      db_get_object_args
      {
         .space = space,
         .key = key,
         .object_size_hint = object_size_hint
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::db_get_object,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );

   return detail::return_buf;
}

variable_blob db_get_next_object( const uint256& space, const uint256& key, int32_t object_size_hint )
{
   auto args = pack::to_variable_blob(
      db_get_next_object_args
      {
         .space = space,
         .key = key,
         .object_size_hint = object_size_hint
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::db_get_next_object,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );

   return detail::return_buf;
}

variable_blob db_get_prev_object( const uint256& space, const uint256& key, int32_t object_size_hint )
{
   auto args = pack::to_variable_blob(
      db_get_prev_object_args
      {
         .space = space,
         .key = key,
         .object_size_hint = object_size_hint
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::db_get_prev_object,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );

   return detail::return_buf;
}

variable_blob execute_contract( const contract_id_type& contract_id, uint32_t entry_point, const variable_blob& contract_args )
{
   auto args = pack::to_variable_blob(
      execute_contract_args
      {
         .contract_id = contract_id,
         .entry_point = entry_point,
         .args = contract_args
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::execute_contract,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );

   return detail::return_buf;
}

head_info get_head_info()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_head_info,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );

   return pack::from_variable_blob< head_info >( detail::return_buf );
}

multihash_type hash( uint64_t code, const variable_blob& obj, uint64_t size )
{
   auto args = pack::to_variable_blob(
      hash_args
      {
         .code = code,
         .obj  = obj,
         .size = size
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::hash,
      args.data(),
      args.size(),
      detail::return_buf.data(),
      detail::return_buf.size()
   );

   return pack::from_variable_blob< multihash_type >( detail::return_buf );
}

} // koinos::system
