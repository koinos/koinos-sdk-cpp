#pragma once

#include <string>
#include <utility>

#include <koinos/chain/chain.h>
#include <koinos/protocol/protocol.h>

#include <koinos/buffer.hpp>
#include <koinos/common.h>

namespace koinos::system {

namespace detail {
   constexpr std::size_t max_hash_size          = 67;
   constexpr std::size_t max_active_data_size   = 1 << 20;
   constexpr std::size_t max_passive_data_size  = 1 << 20;
   constexpr std::size_t max_argument_size      = 2048;
   constexpr std::size_t max_buffer_size        = 1 << 20;
   constexpr std::size_t max_transaction_length = 512;
   constexpr std::size_t max_contract_size      = 2 << 20;
   constexpr std::size_t max_space_size         = 32;
   constexpr std::size_t max_key_size           = 32;
}

using block = koinos::protocol::block<
   detail::max_hash_size,
   detail::max_hash_size,
   detail::max_active_data_size,
   detail::max_passive_data_size,
   detail::max_hash_size,
   detail::max_transaction_length,
   detail::max_hash_size,
   detail::max_active_data_size,
   detail::max_passive_data_size,
   detail::max_hash_size >;

using transaction = koinos::protocol::transaction<
   detail::max_hash_size,
   detail::max_active_data_size,
   detail::max_passive_data_size,
   detail::max_hash_size >;

using upload_contract_operation = koinos::protocol::upload_contract_operation<
   detail::max_hash_size,
   detail::max_contract_size >;

using call_contract_operation = koinos::protocol::call_contract_operation<
   detail::max_hash_size,
   detail::max_argument_size >;

using set_system_call_operation = koinos::protocol::set_system_call_operation< detail::max_argument_size >;
using head_info = koinos::chain::head_info< detail::max_hash_size, detail::max_hash_size >;

void print( const std::string& s );

bool verify_block_signature( const std::string& digest, const std::string& active_data, const std::string& sig );

void apply_block( const block& b, bool check_passive_data, bool check_block_signature, bool check_transaction_signatures );

void apply_transaction( const transaction& t );

void apply_upload_contract_operation( const upload_contract_operation& o );

void apply_call_contract_operation( const call_contract_operation& op );

void apply_set_system_call_operation( const set_system_call_operation& op );

bool put_object( const std::string& space, const std::string& key, const std::string& obj );

template< typename T >
bool put_object( const std::string& space, const std::string& key, const T& value )
{
   std::array< uint8_t, detail::max_argument_size > buf;
   koinos::write_buffer buffer( buf.data(), buf.size() );
   value.serialize( buffer );
   return put_object( space, key, std::string( reinterpret_cast< char* >( buf.data() ), buffer.get_size() ) );
}

std::string get_object( const std::string& space, const std::string& key, int32_t object_size_hint = -1 );

template< typename T >
bool get_object( const std::string& space, const std::string& key, T& t )
{
   auto obj = get_object( space, key );
   if ( obj.size() )
   {
      koinos::read_buffer buffer( reinterpret_cast< uint8_t* >( obj.data() ), obj.size() );
      t.deserialize( buffer );
      return true;
   }

   return false;
}

std::string get_next_object( const std::string& space, const std::string& key, int32_t object_size_hint = -1 );

std::string get_prev_object( const std::string& space, const std::string& key, int32_t object_size_hint = -1 );

std::string call_contract( const std::string& contract_id, uint32_t entry_point, const std::string& contract_args );

uint32_t get_entry_point();

uint32_t get_contract_args_size();

std::string get_contract_args();

template< typename T >
T get_contract_args()
{
   std::string args = get_contract_args();
   T t;
   t.ParseFromString( args );
   return t;
}

void set_contract_return_bytes( const std::string& ret );

void set_contract_return( const std::string& ret );

template< typename T >
void set_contract_return( T&& t )
{
   std::string obj;
   t.SerializeToString( &obj );
   set_contract_return_bytes( obj );
}

void exit_contract( uint8_t exit_code );

head_info get_head_info();

std::string hash( uint64_t code, const std::string& obj, uint64_t size = 0 );

std::string recover_public_key( const std::string& signature_data, const std::string& digest );

bool verify_merkle_root( const std::string& root, const std::vector< std::string >& hashes );

std::string get_transaction_payer( const transaction& trx );

uint64_t get_max_account_resources( const std::string& account );

uint64_t get_transaction_resource_limit( const transaction& trx );

uint64_t get_last_irreversible_block();

std::pair< std::string, koinos::chain::privilege > get_caller();

void require_authority( const std::string& account );

std::string get_transaction_signature();

std::string get_contract_id();

} // koinos::system
