#pragma once
#include <koinos/pack/classes.hpp>

namespace koinos::system {

using namespace koinos::chain;

void print( const std::string& s );

bool verify_block_signature( const multihash& digest, opaque< protocol::active_block_data >& active_data, const variable_blob& sig );

void apply_block( const protocol::block& b, bool enable_check_passive_data, bool enable_check_block_signature, bool enable_check_transaction_signatures );

void apply_transaction( const protocol::transaction& t );

void apply_reserved_operation( const protocol::reserved_operation& o );

void apply_upload_contract_operation( const protocol::create_system_contract_operation& o );

void apply_execute_contract_operation( const protocol::call_contract_operation& op );

void apply_set_system_call_operation( const protocol::set_system_call_operation& op );

bool db_put_object( const uint256& space, const uint256& key, const variable_blob& obj );

template< typename T >
bool db_put_object( const uint256& space, const uint256& key, const T& value )
{
   return db_put_object( space, key, pack::to_variable_blob( value ) );
}

template< typename T >
bool db_put_object( const uint256& space, variable_blob vb_key, const T& value )
{
   vb_key.resize( 32, char(0) );
   auto key = pack::from_variable_blob< uint256 >( vb_key );

   return system::db_put_object( space, key, pack::to_variable_blob( value ) );
}

variable_blob db_get_object( const uint256& space, const uint256& key, int32_t object_size_hint = -1 );

template< typename T >
bool db_get_object( const uint256& space, const uint256& key, T& t )
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
bool db_get_object( const uint256& space, variable_blob vb_key, T& t )
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

variable_blob db_get_next_object( const uint256& space, const uint256& key, int32_t object_size_hint = -1 );

variable_blob db_get_prev_object( const uint256& space, const uint256& key, int32_t object_size_hint = -1 );

variable_blob execute_contract( const contract_id_type& contract_id, uint32_t entry_point, const variable_blob& contract_args );

uint32_t get_entry_point();

uint32_t get_contract_args_size();

variable_blob get_contract_args();

template< typename T >
T get_contract_args()
{
   return pack::from_variable_blob< T >( get_contract_args() );
}

void set_contract_return_vb( const variable_blob& ret );

void set_contract_return( const variable_blob& ret );

template< typename T >
void set_contract_return( T&& t )
{
   set_contract_return_vb( pack::to_variable_blob( t ) );
}

void exit_contract( uint8_t exit_code );

chain::head_info get_head_info();

multihash hash( uint64_t code, const variable_blob& obj, uint64_t size = 0 );

protocol::account_type recover_public_key( const variable_blob& signature_data, const multihash& digest );

bool verify_merkle_root( const multihash& root, const std::vector< multihash >& hashes );

protocol::account_type get_transaction_payer( const protocol::transaction& trx );

uint128 get_max_account_resources( const protocol::account_type& account );

uint128 get_transaction_resource_limit( const protocol::transaction& trx );

block_height_type get_last_irreversible_block();

get_caller_return get_caller();

void require_authority( const protocol::account_type& account );

variable_blob get_transaction_signature();

contract_id_type get_contract_id();

timestamp_type get_head_block_time();

} // koinos::system
