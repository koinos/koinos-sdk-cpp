#pragma once
#include <array>
#include <string>
#include <utility>
#include <vector>

#include <koinos/system/system_calls.hpp>

#include <koinos/protocol/system_call_ids.h>

#include <koinos/chain/system_calls.h>
#include <koinos/protocol/protocol.h>

#include <koinos/buffer.hpp>
#include <koinos/common.h>

extern "C" uint32_t invoke_system_call( uint32_t sid, char* ret_ptr, uint32_t ret_len, char* arg_ptr, uint32_t arg_len );

namespace koinos::system {

namespace detail {
   constexpr std::size_t max_hash_size          = 67;
   constexpr std::size_t max_signature_size   = 10 * max_hash_size;
   constexpr std::size_t max_active_data_size   = 1 << 10;
   constexpr std::size_t max_argument_size      = 2048;
   constexpr std::size_t max_buffer_size        = 1 << 10;
   constexpr std::size_t max_transaction_length = 512;
   constexpr std::size_t max_operation_length   = 64;
   constexpr std::size_t max_contract_size      = 2 << 10;
   constexpr std::size_t max_contract_abi_size  = 2 << 10;
   constexpr std::size_t max_space_size         = 32;
   constexpr std::size_t max_key_size           = 32;
   constexpr std::size_t zone_size              = 128;
   constexpr std::size_t max_event_name_size    = 32;
   constexpr std::size_t max_event_size         = 1024;
   constexpr std::size_t max_address_size       = 25;
   constexpr std::size_t max_impacted_size      = 10;
   static std::array< uint8_t, max_buffer_size > syscall_buffer;
}

using object_space = koinos::chain::object_space< detail::zone_size >;

using put_object_arguments = koinos::chain::put_object_arguments< detail::zone_size, detail::max_key_size, detail::max_argument_size >;
using get_object_arguments = koinos::chain::get_object_arguments< detail::zone_size, detail::max_key_size >;
using get_next_object_arguments = koinos::chain::get_next_object_arguments< detail::zone_size, detail::max_key_size >;
using get_prev_object_arguments = koinos::chain::get_prev_object_arguments< detail::zone_size, detail::max_key_size >;

using block = koinos::protocol::block<
   detail::max_hash_size,
   detail::max_hash_size,
   detail::max_hash_size,
   detail::max_signature_size,
   detail::max_address_size,
   detail::max_transaction_length,
   detail::max_hash_size,
   detail::max_hash_size,
   detail::max_operation_length,
   detail::max_address_size,
   detail::max_contract_size,
   detail::max_contract_size,
   detail::max_address_size,
   detail::max_argument_size,
   detail::max_argument_size,
   detail::max_address_size,
   detail::max_signature_size,
   detail::max_signature_size >;

using block_header = koinos::protocol::block_header<
   detail::max_hash_size,
   detail::max_hash_size,
   detail::max_hash_size,
   detail::max_address_size >;

using transaction = koinos::protocol::transaction<
   detail::max_hash_size,
   detail::max_hash_size,
   detail::max_operation_length,
   detail::max_address_size,
   detail::max_contract_size,
   detail::max_contract_size,
   detail::max_address_size,
   detail::max_argument_size,
   detail::max_argument_size,
   detail::max_address_size,
   detail::max_signature_size >;

using upload_contract_operation = koinos::protocol::upload_contract_operation<
   detail::max_hash_size,
   detail::max_contract_size,
   detail::max_contract_size >;

using call_contract_operation = koinos::protocol::call_contract_operation<
   detail::max_hash_size,
   detail::max_argument_size >;

using set_system_call_operation = koinos::protocol::set_system_call_operation< detail::max_argument_size >;
using head_info = koinos::chain::head_info< detail::max_hash_size, detail::max_hash_size >;

inline void print( const std::string& s )
{
   koinos::chain::prints_arguments< detail::max_argument_size > args;
   args.mutable_message() = s.c_str();

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );


   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::prints ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );
}

inline bool process_block_signature( const std::string& digest, const block_header& header, const std::string& sig )
{
   koinos::chain::process_block_signature_arguments<
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_address_size,
      detail::max_signature_size > args;

   args.mutable_digest().set( reinterpret_cast< const uint8_t* >( digest.data() ), digest.size() );
   args.mutable_header() = header;
   args.mutable_signature().set( reinterpret_cast< const uint8_t* >( sig.data() ), sig.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::process_block_signature ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::process_block_signature_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline void apply_block( const block& b, bool check_passive_data, bool check_block_signature, bool check_transaction_signatures )
{
   koinos::chain::apply_block_arguments<
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_signature_size,
      detail::max_address_size,
      detail::max_transaction_length,
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_operation_length,
      detail::max_address_size,
      detail::max_contract_size,
      detail::max_contract_size,
      detail::max_address_size,
      detail::max_argument_size,
      detail::max_argument_size,
      detail::max_address_size,
      detail::max_signature_size,
      detail::max_signature_size > args;
   args.mutable_block() = b;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::apply_block ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );
}

inline void apply_transaction( const transaction& t )
{
   koinos::chain::apply_transaction_arguments<
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_operation_length,
      detail::max_address_size,
      detail::max_contract_size,
      detail::max_contract_size,
      detail::max_address_size,
      detail::max_argument_size,
      detail::max_argument_size,
      detail::max_address_size,
      detail::max_signature_size > args;
   args.mutable_transaction() = t;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::apply_transaction ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );
}

inline void apply_upload_contract_operation( const upload_contract_operation& o )
{
   koinos::chain::apply_upload_contract_operation_arguments<
      detail::max_hash_size,
      detail::max_contract_size,
      detail::max_contract_size  > args;
   args.mutable_op() = o;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::apply_upload_contract_operation ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );
}

inline void apply_call_contract_operation( const call_contract_operation& o )
{
   koinos::chain::apply_call_contract_operation_arguments<
      detail::max_hash_size,
      detail::max_argument_size > args;
   args.mutable_op() = o;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::apply_call_contract_operation ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );
}

inline void apply_set_system_call_operation( const set_system_call_operation& o )
{
   koinos::chain::apply_set_system_call_operation_arguments< detail::max_argument_size > args;
   args.mutable_op() = o;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::apply_set_system_call_operation ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );
}

inline std::string get_next_object( const object_space& space, const std::string& key, uint32_t object_size_hint = 0 )
{
   get_next_object_arguments args;
   args.mutable_space() = space;
   args.mutable_key().set( reinterpret_cast< const uint8_t* >( key.data() ), key.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_next_object ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_next_object_result< detail::max_argument_size, detail::max_key_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_value().get_const() ), res.get_value().get_value().get_length() );
}

inline std::string get_prev_object( const object_space& space, const std::string& key, uint32_t object_size_hint = 0 )
{
   get_prev_object_arguments args;
   args.mutable_space() = space;
   args.mutable_key().set( reinterpret_cast< const uint8_t* >( key.data() ), key.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_prev_object ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_prev_object_result< detail::max_argument_size, detail::max_key_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_value().get_const() ), res.get_value().get_value().get_length() );
}

inline std::string call_contract( const std::string& contract_id, uint32_t entry_point, const std::string& contract_args )
{
   koinos::chain::call_contract_arguments< detail::max_hash_size, detail::max_argument_size > args;
   args.mutable_contract_id().set( reinterpret_cast< const uint8_t* >( contract_id.data() ), contract_id.size() );
   args.mutable_entry_point() = entry_point;
   args.mutable_args().set( reinterpret_cast< const uint8_t* >( contract_args.data() ), contract_args.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::call_contract ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::call_contract_result< detail::max_argument_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_const() ), res.get_value().get_length() );
}

inline uint32_t get_entry_point()
{
   koinos::chain::get_entry_point_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_entry_point ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_entry_point_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline uint32_t get_contract_arguments_size()
{
   koinos::chain::get_contract_arguments_size_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_contract_arguments_size ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_contract_arguments_size_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline std::string get_contract_arguments()
{
   koinos::chain::get_contract_arguments_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_contract_arguments ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_contract_arguments_result< detail::max_argument_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_const() ), res.get_value().get_length() );
}

inline void set_contract_result_bytes( const std::string& res )
{
   koinos::chain::set_contract_result_arguments< detail::max_argument_size > args;
   args.mutable_value().set( reinterpret_cast< const uint8_t* >( res.data() ), res.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::set_contract_result ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );
}

inline void exit_contract( uint32_t exit_code )
{
   koinos::chain::exit_contract_arguments args;
   args.mutable_exit_code() = exit_code;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::exit_contract ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );
}

inline head_info get_head_info()
{
   koinos::chain::get_head_info_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_head_info ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_head_info_result< detail::max_hash_size, detail::max_hash_size > res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline std::string hash( uint64_t code, const std::string& obj, uint64_t size = 0 )
{
   koinos::chain::hash_arguments< detail::max_argument_size > args;
   args.mutable_code() = code;
   args.mutable_obj().set( reinterpret_cast< const uint8_t* >( obj.data() ), obj.size() );
   args.mutable_size() = size;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::hash ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::hash_result< detail::max_hash_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_const() ), res.get_value().get_length() );
}

inline std::string recover_public_key( const std::string& signature_data, const std::string& digest )
{
   koinos::chain::recover_public_key_arguments< detail::max_hash_size, detail::max_hash_size > args;
   args.mutable_digest().set( reinterpret_cast< const uint8_t* >( digest.data() ), digest.size() );
   args.mutable_signature_data().set( reinterpret_cast< const uint8_t* >( signature_data.data() ), signature_data.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::recover_public_key ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::recover_public_key_result< detail::max_hash_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_const() ), res.get_value().get_length() );
}

inline bool verify_merkle_root( const std::string& root, const std::vector< std::string >& hashes )
{
   koinos::chain::process_block_signature_arguments<
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_address_size,
      detail::max_signature_size > args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::verify_merkle_root ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::process_block_signature_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

/*
inline std::string get_transaction_payer( const transaction& trx )
{
   koinos::chain::get_transaction_payer_arguments<
      detail::max_hash_size,
      detail::max_active_data_size,
      detail::max_hash_size > args;
   args.mutable_transaction() = trx;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_transaction_payer ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_transaction_payer_result< detail::max_hash_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_const() ), res.get_value().get_length() );
}
*/

inline uint64_t get_account_rc( const std::string& account )
{
   koinos::chain::get_account_rc_arguments< detail::max_hash_size > args;
   args.mutable_account().set( reinterpret_cast< const uint8_t* >( account.data() ), account.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_account_rc ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_account_rc_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

/*
inline uint64_t get_transaction_rc_limit( const transaction& trx )
{
   koinos::chain::get_transaction_rc_limit_arguments<
      detail::max_hash_size,
      detail::max_active_data_size,
      detail::max_hash_size > args;
   args.mutable_transaction() = trx;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_transaction_rc_limit ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_transaction_rc_limit_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}
*/

inline uint64_t get_last_irreversible_block()
{
   koinos::chain::get_last_irreversible_block_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_last_irreversible_block ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_last_irreversible_block_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline std::pair< std::string, koinos::chain::privilege > get_caller()
{
   koinos::chain::get_caller_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_caller ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_caller_result< detail::max_hash_size > res;
   res.deserialize( rdbuf );

   auto value = res.value();
   return std::make_pair( std::string( reinterpret_cast< const char* >( value.get_caller().get_const() ), value.get_caller().get_length() ), value.get_caller_privilege() );
}

inline void require_authority( const std::string& account )
{
   koinos::chain::require_authority_arguments< detail::max_hash_size > args;
   args.mutable_account().set( reinterpret_cast< const uint8_t* >( account.data() ), account.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::require_authority ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );
}

inline std::string get_transaction_signature()
{
   koinos::chain::get_transaction_signature_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_transaction_signature ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_transaction_signature_result< detail::max_hash_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_const() ), res.get_value().get_length() );
}

inline std::string get_contract_id()
{
   koinos::chain::get_contract_id_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_contract_id ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_contract_id_result< detail::max_hash_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_const() ), res.get_value().get_length() );
}

namespace detail {

inline bool put_object( const object_space& space, const std::string& key, const std::string& obj )
{
   if ( key.size() > detail::max_key_size )
   {
      std::string err_msg = "key size exceeds max size of " + std::to_string( detail::max_key_size );
      print( err_msg );
      exit_contract( 1 );
   }

   put_object_arguments args;
   args.mutable_space() = space;
   args.mutable_key().set( reinterpret_cast< const uint8_t* >( key.data() ), key.size() );
   args.mutable_obj().set( reinterpret_cast< const uint8_t* >( obj.data() ), obj.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::put_object ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::put_object_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline std::string get_object( const object_space& space, const std::string& key, uint32_t object_size_hint = 0 )
{
   if ( key.size() > detail::max_key_size )
   {
      std::string err_msg = "key size exceeds max size of " + std::to_string( detail::max_key_size );
      print( err_msg );
      exit_contract( 1 );
   }

   get_object_arguments args;
   args.mutable_space() = space;
   args.mutable_key().set( reinterpret_cast< const uint8_t* >( key.data() ), key.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::get_object ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), ret_size );

   koinos::chain::get_object_result< detail::max_argument_size, detail::max_key_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_value().get_const() ), res.get_value().get_value().get_length() );
}

} // detail

template< typename T >
bool put_object( const object_space& space, const std::string& key, const T& value )
{
   std::array< uint8_t, detail::max_argument_size > buf;
   koinos::write_buffer buffer( buf.data(), buf.size() );
   value.serialize( buffer );
   return detail::put_object( space, key, std::string( reinterpret_cast< char* >( buffer.data() ), buffer.get_size() ) );
}

template< typename T >
bool get_object( const object_space& space, const std::string& key, T& t )
{
   auto obj = detail::get_object( space, key );
   if ( obj.size() )
   {
      koinos::read_buffer buffer( reinterpret_cast< uint8_t* >( obj.data() ), obj.size() );
      t.deserialize( buffer );
      return true;
   }

   return false;
}

template< typename T >
void set_contract_result( T&& t )
{
   std::string obj;
   t.SerializeToString( &obj );
   set_contract_result_bytes( obj );
}

template< typename T >
inline void event( const std::string& name, const T& data, const std::vector< std::string >& impacted = {} )
{
   if ( impacted.size() > detail::max_impacted_size )
   {
      std::string err_msg = "impacted size exceeds max size of " + std::to_string( detail::max_impacted_size );
      print( err_msg );
      exit_contract( 1 );
   }

   std::array< uint8_t, detail::max_argument_size > buf;
   koinos::write_buffer wbuf( buf.data(), buf.size() );
   data.serialize( wbuf );

   koinos::chain::event_arguments< detail::max_event_name_size, detail::max_event_size, detail::max_impacted_size, detail::max_address_size > args;
   args.mutable_name() = name.c_str();
   args.mutable_data().set( wbuf.data(), wbuf.get_size() );

   for ( const auto& s : impacted )
   {
      ::EmbeddedProto::FieldBytes< detail::max_address_size > value;
      value.set( reinterpret_cast< const uint8_t* >( s.data() ), s.size() );
      args.add_impacted( value );
   }

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t ret_size = invoke_system_call(
      std::underlying_type_t< koinos::protocol::system_call_id >( koinos::protocol::system_call_id::event ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size()
   );
}

} // koinos::system
