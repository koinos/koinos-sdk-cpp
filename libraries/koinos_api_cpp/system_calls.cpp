#include <koinos/system/system_calls.hpp>

#define KOINOS_SYSTEM_MAX_RET_BUFFER 1 << 20

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
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );
}

uint32_t get_contract_args_size()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_contract_args_size,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< uint32_t >( detail::return_buf );
}

variable_blob get_contract_args()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_contract_args,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
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
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );
}

bool verify_block_sig( const types::variable_blob& sig_data, const types::multihash& digest )
{
   auto args = pack::to_variable_blob( verify_block_sig_args{ .sig_data = sig_data, .digest = digest } );

   invoke_system_call(
      (uint32_t)system_call_id::verify_block_sig,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< bool >( detail::return_buf );
}

bool verify_merkle_root( const types::multihash& root, const std::vector< types::multihash >& hashes )
{
   auto args = pack::to_variable_blob( verify_merkle_root_args{ .root = root, .hashes = hashes } );

   invoke_system_call(
      (uint32_t)system_call_id::verify_merkle_root,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< bool >( detail::return_buf );
}

void apply_block( const types::protocol::block& block, bool enable_check_passive_data, bool enable_check_block_signature, bool enable_check_transaction_signatures )
{
   auto args = pack::to_variable_blob( apply_block_args
   {
      .block = block,
      .enable_check_passive_data = enable_check_passive_data,
      .enable_check_block_signature = enable_check_block_signature,
      .enable_check_transaction_signatures = enable_check_transaction_signatures
   } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_block,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );
}

void apply_transaction( const types::opaque< types::protocol::transaction > trx )
{
   auto args = pack::to_variable_blob( apply_transaction_args{ .trx = trx } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_transaction,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );
}

void apply_reserved_operation( const protocol::reserved_operation& o )
{
   auto args = pack::to_variable_blob( apply_reserved_operation_args{ .op = o } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_reserved_operation,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );
}

void apply_upload_contract_operation( const protocol::create_system_contract_operation& o )
{
   auto args = pack::to_variable_blob( apply_upload_contract_operation_args{ .op = o } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_upload_contract_operation,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );
}

void apply_execute_contract_operation( const protocol::contract_call_operation& o )
{
   auto args = pack::to_variable_blob( apply_execute_contract_operation_args{ .op = o } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_execute_contract_operation,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );
}

void apply_set_system_call_operation( const protocol::set_system_call_operation& o )
{
   auto args = pack::to_variable_blob( apply_set_system_call_operation_args{ .op = o } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_set_system_call_operation,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
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
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
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
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
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
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
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
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
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
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return detail::return_buf;
}

head_info get_head_info()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_head_info,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< head_info >( detail::return_buf );
}

multihash hash( uint64_t code, const variable_blob& obj, uint64_t size )
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
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< multihash >( detail::return_buf );
}

} // koinos::system
