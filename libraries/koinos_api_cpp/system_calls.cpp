#include <koinos/system/system_calls.hpp>

#include <koinos/pack/rt/binary.hpp>
#include <koinos/pack/system_call_ids.hpp>

#define KOINOS_SYSTEM_MAX_RET_BUFFER 1 << 20

extern "C" void invoke_system_call( uint32_t sid, char* ret_ptr, uint32_t ret_len, char* arg_ptr, uint32_t arg_len );

namespace koinos::system {

using namespace koinos::chain;

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

bool verify_block_signature( const multihash& digest, opaque< protocol::active_block_data >& active_data, const variable_blob& sig )
{
   auto args = pack::to_variable_blob( verify_block_signature_args {
      .digest = digest,
      .active_data = active_data,
      .signature_data = sig
   } );

   invoke_system_call(
      (uint32_t)system_call_id::verify_block_signature,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< bool >( detail::return_buf );
}

void apply_block( const protocol::block& b, bool enable_check_passive_data, bool enable_check_block_signature, bool enable_check_transaction_signatures )
{
   auto args = pack::to_variable_blob( apply_block_args{
      .block = b,
      .check_passive_data = enable_check_passive_data,
      .check_block_signature = enable_check_block_signature,
      .check_transaction_signatures = enable_check_transaction_signatures } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_block,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );
}

void apply_transaction( const protocol::transaction& t )
{
   auto args = pack::to_variable_blob( apply_transaction_args{ .transaction = t } );

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

void apply_execute_contract_operation( const protocol::call_contract_operation& op )
{
   auto args = pack::to_variable_blob( apply_execute_contract_operation_args{ .op = op } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_execute_contract_operation,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );
}

void apply_set_system_call_operation( const protocol::set_system_call_operation& op )
{
   auto args = pack::to_variable_blob( apply_set_system_call_operation_args{ .op = op } );

   invoke_system_call(
      (uint32_t)system_call_id::apply_set_system_call_operation,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );
}

bool db_put_object( const uint256& space, const uint256& key, const variable_blob& obj );

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

variable_blob db_get_object( const uint256& space, const uint256& key, int32_t object_size_hint );

variable_blob db_get_object( const uint256& space, const uint256& key, int32_t object_size_hint ){
   auto args = pack::to_variable_blob(
      db_get_object_args
      {
         .space = space,
         .key = key,
         .object_size_hint = object_size_hint
      }
   );

   // Read data is returned as a variable blob, which will change this value if a value is returned.
   detail::return_buf[0] = uint8_t(0);

   invoke_system_call(
      (uint32_t)system_call_id::db_get_object,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< variable_blob >( detail::return_buf );
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

uint32_t get_entry_point()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_entry_point,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< uint32_t >( detail::return_buf );
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

   return pack::from_variable_blob< get_contract_args_return >( detail::return_buf );
}

void set_contract_return_vb( const variable_blob& ret )
{
   auto args = pack::to_variable_blob(
      set_contract_return_args
      {
         .value = ret
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

void set_contract_return( const variable_blob& ret )
{
   set_contract_return_vb( ret );
}

void exit_contract( uint8_t exit_code )
{
   auto args = pack::to_variable_blob(
      exit_contract_args
      {
         .exit_code = exit_code
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::exit_contract,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );
}

chain::head_info get_head_info()
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

protocol::account_type recover_public_key( const variable_blob& signature_data, const multihash& digest )
{
   auto args = pack::to_variable_blob(
      recover_public_key_args
      {
         .signature_data = signature_data,
         .digest         = digest,
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::recover_public_key,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< protocol::account_type >( detail::return_buf );
}

bool verify_merkle_root( const multihash& root, const std::vector< multihash >& hashes )
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


protocol::account_type get_transaction_payer( const protocol::transaction& trx )
{
   auto args = pack::to_variable_blob(
      get_transaction_payer_args
      {
         .transaction = trx
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::get_transaction_payer,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< protocol::account_type >( detail::return_buf );
}

uint128 get_max_account_resources( const protocol::account_type& account )
{
   variable_blob args = pack::to_variable_blob(
      get_max_account_resources_args
      {
         .account = account
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::get_max_account_resources,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< uint128 >( detail::return_buf );
}

uint128 get_transaction_resource_limit( const protocol::transaction& trx )
{
   auto args = pack::to_variable_blob(
      get_transaction_resource_limit_args
      {
         .transaction = trx
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::get_transaction_resource_limit,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< uint128 >( detail::return_buf );
}

block_height_type get_last_irreversible_block()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_last_irreversible_block,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< block_height_type >( detail::return_buf );
}

get_caller_return get_caller()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_caller,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< get_caller_return >( detail::return_buf );
}

void require_authority( const protocol::account_type& account )
{
   auto args = pack::to_variable_blob(
      require_authority_args
      {
         .account = account
      }
   );

   invoke_system_call(
      (uint32_t)system_call_id::require_authority,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );
}

variable_blob get_transaction_signature()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_transaction_signature,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< protocol::account_type >( detail::return_buf );
}

contract_id_type get_contract_id()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_contract_id,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< contract_id_type >( detail::return_buf );
}

timestamp_type get_head_block_time()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_head_block_time,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< timestamp_type >( detail::return_buf );
};

} // koinos::system
