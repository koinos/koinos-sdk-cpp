#pragma once
#include <koinos/pack/rt/binary.hpp>
#include <koinos/pack/classes.hpp>
#include <koinos/pack/system_call_ids.hpp>

#define KOINOS_SYSTEM_MAX_RET_BUFFER 1 << 20

extern "C" void invoke_system_call( uint32_t sid, char* ret_ptr, uint32_t ret_len, char* arg_ptr, uint32_t arg_len );

namespace koinos::system {

namespace detail {
   static variable_blob return_buf( KOINOS_SYSTEM_MAX_RET_BUFFER );
}

using namespace koinos::chain;
using chain::account_type;

inline void print( const std::string& s )
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

inline bool verify_block_signature( const variable_blob& sig, const multihash& digest )
{
   auto args = pack::to_variable_blob( verify_block_signature_args{ .signature_data = sig, .digest = digest } );

   invoke_system_call(
      (uint32_t)system_call_id::verify_block_signature,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< bool >( detail::return_buf );
}

inline void apply_block( const protocol::block& b, bool enable_check_passive_data, bool enable_check_block_signature, bool enable_check_transaction_signatures )
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

inline void apply_transaction( const protocol::transaction& t )
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

inline void apply_reserved_operation( const protocol::reserved_operation& o )
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

inline void apply_upload_contract_operation( const protocol::create_system_contract_operation& o )
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

inline void apply_execute_contract_operation( const protocol::call_contract_operation& op )
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

inline void apply_set_system_call_operation( const protocol::set_system_call_operation& op )
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

inline bool db_put_object( const uint256& space, const uint256& key, const variable_blob& obj );

template< typename T >
inline bool db_put_object( const uint256& space, const uint256& key, const T& value )
{
   return db_put_object( space, key, pack::to_variable_blob( value ) );
}

template< typename T >
inline bool db_put_object( const uint256& space, variable_blob vb_key, const T& value )
{
   vb_key.resize( 32, char(0) );
   auto key = pack::from_variable_blob< uint256 >( vb_key );

   return system::db_put_object( space, key, pack::to_variable_blob( value ) );
}

inline bool db_put_object( const uint256& space, const uint256& key, const variable_blob& obj )
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

inline variable_blob db_get_object( const uint256& space, const uint256& key, int32_t object_size_hint = -1 );

template< typename T >
inline bool db_get_object( const uint256& space, const uint256& key, T& t )
{
   auto vb = db_get_object( space, key, sizeof( T ) );
   if( vb.size() )
   {
      t = pack::from_variable_blob< T >( vb );
      return true;
   }

   return false;
}

template< typename T >
inline bool db_get_object( const uint256& space, variable_blob vb_key, T& t )
{
   vb_key.resize( 32, char(0) );
   auto key = pack::from_variable_blob< uint256 >( vb_key );

   auto vb = db_get_object( space, key, sizeof( T ) );
   if( vb.size() )
   {
      t = pack::from_variable_blob< T >( vb );
      return true;
   }

   return false;
}

inline variable_blob db_get_object( const uint256& space, const uint256& key, int32_t object_size_hint ){
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

inline variable_blob db_get_next_object( const uint256& space, const uint256& key, int32_t object_size_hint = -1 )
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

inline variable_blob db_get_prev_object( const uint256& space, const uint256& key, int32_t object_size_hint = -1 )
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

inline variable_blob execute_contract( const contract_id_type& contract_id, uint32_t entry_point, const variable_blob& contract_args )
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

inline uint32_t get_entry_point()
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

inline uint32_t get_contract_args_size()
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

inline variable_blob get_contract_args()
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

template< typename T >
inline T get_contract_args()
{
   return pack::from_variable_blob< T >( get_contract_args() );
}

inline void set_contract_return( const variable_blob& ret )
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

template< typename T >
inline void set_contract_return( T&& t )
{
   set_contract_return( pack::to_variable_blob( t ) );
}

inline void exit_contract( uint8_t exit_code )
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

inline chain::head_info get_head_info()
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

inline multihash hash( uint64_t code, const variable_blob& obj, uint64_t size = 0 )
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

inline account_type recover_public_key( const variable_blob& signature_data, const multihash& digest )
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

   return pack::from_variable_blob< account_type >( detail::return_buf );
}

inline bool verify_merkle_root( const multihash& root, const std::vector< multihash >& hashes )
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


inline account_type get_transaction_payer( const protocol::transaction& trx )
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

   return pack::from_variable_blob< account_type >( detail::return_buf );
}

inline uint128 get_max_account_resources( const account_type& account )
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

inline uint128 get_transaction_resource_limit( const protocol::transaction& trx )
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

inline block_height_type get_last_irreversible_block()
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

inline get_caller_return get_caller()
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

inline void require_authority( const account_type& account )
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

inline variable_blob get_transaction_signature()
{
   variable_blob args;

   invoke_system_call(
      (uint32_t)system_call_id::get_transaction_signature,
      detail::return_buf.data(),
      detail::return_buf.size(),
      args.data(),
      args.size()
   );

   return pack::from_variable_blob< account_type >( detail::return_buf );
}

inline contract_id_type get_contract_id()
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

} // koinos::system
