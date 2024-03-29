#pragma once
#include <array>
#include <string>
#include <utility>
#include <vector>

#include <koinos/any.hpp>

namespace koinos::system::detail {

constexpr std::size_t max_hash_size          = 67;
constexpr std::size_t max_hashes_length      = 512;
constexpr std::size_t max_signatures_length  = 16;
constexpr std::size_t max_signature_size     = 2 * max_hash_size;
constexpr std::size_t max_active_data_size   = 1 << 10;
constexpr std::size_t max_argument_size      = 2048;
constexpr std::size_t max_buffer_size        = 1 << 12;
constexpr std::size_t max_transaction_length = 512;
constexpr std::size_t max_operation_length   = 64;
constexpr std::size_t max_contract_size      = 2 << 10;
constexpr std::size_t max_contract_abi_size  = 2 << 10;
constexpr std::size_t max_space_size         = 32;
constexpr std::size_t max_key_size           = max_hash_size;
constexpr std::size_t zone_size              = 128;
constexpr std::size_t max_event_name_size    = 128;
constexpr std::size_t max_event_size         = 1024;
constexpr std::size_t max_address_size       = 25;
constexpr std::size_t max_impacted_size      = 10;
constexpr std::size_t max_field_name_length  = 128;
constexpr std::size_t max_field_size         = max_signatures_length * max_signature_size;
constexpr std::size_t max_public_key_size    = 33;
constexpr std::size_t max_nonce_size         = max_hash_size;
constexpr std::size_t max_proposal_length    = 32;
static std::array< uint8_t, max_buffer_size > syscall_buffer;

} // koinos::system::detail

namespace google::protobuf {

using Any = koinos::Any< koinos::system::detail::max_field_name_length, koinos::system::detail::max_field_size >;

} // google::protobuf

#include <koinos/system/system_calls.hpp>

#include <koinos/chain/authority.h>
#include <koinos/chain/chain.h>
#include <koinos/chain/error.h>
#include <koinos/chain/system_calls.h>
#include <koinos/chain/system_call_ids.h>
#include <koinos/chain/value.h>
#include <koinos/protocol/protocol.h>

#include <koinos/contracts/name_service/name_service.h>

#include <koinos/buffer.hpp>
#include <koinos/common.h>

extern "C" int32_t invoke_system_call( uint32_t sid, char* ret_ptr, uint32_t ret_len, char* arg_ptr, uint32_t arg_len, uint32_t* bytes_written );

namespace koinos::system {

using object_space = koinos::chain::object_space< detail::zone_size >;

using put_object_arguments = koinos::chain::put_object_arguments< detail::zone_size, detail::max_key_size, detail::max_argument_size >;
using get_object_arguments = koinos::chain::get_object_arguments< detail::zone_size, detail::max_key_size >;
using remove_object_arguments = koinos::chain::remove_object_arguments< detail::zone_size, detail::max_key_size >;
using get_next_object_arguments = koinos::chain::get_next_object_arguments< detail::zone_size, detail::max_key_size >;
using get_prev_object_arguments = koinos::chain::get_prev_object_arguments< detail::zone_size, detail::max_key_size >;
using value_type = koinos::chain::value_type< detail::max_field_size, detail::max_field_size >;
using result = koinos::chain::result< detail::max_argument_size, detail::max_argument_size >;
using exit_arguments = koinos::chain::exit_arguments< detail::max_argument_size, detail::max_argument_size >;

using block = koinos::protocol::block<
   detail::max_hash_size,           // id
   detail::max_hash_size,           // header.previous
   detail::max_hash_size,           // header.previous_state_merkle_root
   detail::max_hash_size,           // header.transaction_merkle_root
   detail::max_address_size,        // header.signer
   detail::max_proposal_length,     // header.approved_proposals length
   detail::max_hash_size,           // header.approved_proposals
   detail::max_transaction_length,  // transactions length
   detail::max_hash_size,           // transactions.id
   detail::max_hash_size,           // transactions.header.chain_id
   detail::max_nonce_size,          // transactions.header.nonce
   detail::max_hash_size,           // transactions.header.operation_merkle_root
   detail::max_address_size,        // transactions.header.payer
   detail::max_address_size,        // transactions.header.payee
   detail::max_operation_length,    // transactions.operations length
   detail::max_address_size,        // transactions.upload_contract.contract_id
   detail::max_contract_size,       // transactions.upload_contract.bytecode
   detail::max_contract_size,       // transactions.upload_contract.abi
   detail::max_address_size,        // transactions.call_contract.contract_id
   detail::max_argument_size,       // transactions.call_contract.args
   detail::max_argument_size,       // transactions.set_system_call.target.system_call_bundle.contract_id
   detail::max_address_size,        // transactions.set_system_contract.contract_id
   detail::max_signatures_length,   // transactions.signatures length
   detail::max_signature_size,      // transactions.signatures
   detail::max_signature_size >;    // signature

using block_header = koinos::protocol::block_header<
   detail::max_hash_size,
   detail::max_hash_size,
   detail::max_hash_size,
   detail::max_address_size,
   detail::max_proposal_length,
   detail::max_hash_size >;

using transaction = koinos::protocol::transaction<
   detail::max_hash_size,           // id
   detail::max_hash_size,           // header.chain_id
   detail::max_nonce_size,          // header.nonce
   detail::max_hash_size,           // header.operation_merkle_root
   detail::max_address_size,        // header.payer
   detail::max_address_size,        // header.payee
   detail::max_operation_length,    // operations length
   detail::max_address_size,        // upload_contract.contract_id
   detail::max_contract_size,       // upload_contract.bytecode
   detail::max_contract_size,       // upload_contract.abi
   detail::max_address_size,        // call_contract.contract_id
   detail::max_argument_size,       // call_contract.args
   detail::max_argument_size,       // set_system_call.target.system_call_bundle.contract_id
   detail::max_address_size,        // set_system_contract.contract_id
   detail::max_signatures_length,   // signatures length
   detail::max_signature_size >;    // signatures

using operation = koinos::protocol::operation<
   system::detail::max_address_size,        // upload_contract.contract_id
   system::detail::max_contract_size,       // upload_contract.bytecode
   system::detail::max_contract_size,       // upload_contract.abi
   system::detail::max_address_size,        // call_contract.contract_id
   system::detail::max_argument_size,       // call_contract.args
   system::detail::max_argument_size,       // set_system_call.target.system_call_bundle.contract_id
   system::detail::max_address_size >;      // set_system_contract.contract_id

using upload_contract_operation = koinos::protocol::upload_contract_operation<
   detail::max_hash_size,
   detail::max_contract_size,
   detail::max_contract_size >;

using call_contract_operation = koinos::protocol::call_contract_operation<
   detail::max_hash_size,
   detail::max_argument_size >;

using set_system_call_operation = koinos::protocol::set_system_call_operation< detail::max_argument_size >;
using set_system_contract_operation = koinos::protocol::set_system_contract_operation< detail::max_address_size >;
using head_info = koinos::chain::head_info< detail::max_hash_size, detail::max_hash_size >;
using error_data = koinos::chain::error_data< detail::max_argument_size >;

inline void log( const std::string& );
inline void exit( int32_t code, const result& r = result() );
inline void revert( const std::string& msg = "", int32_t code = static_cast< int32_t >( chain::error_code::reversion ) );
inline void fail( const std::string& msg = "", int32_t code = static_cast< int32_t >( chain::error_code::failure ) );

// General Blockchain Management

inline head_info get_head_info()
{
   koinos::chain::get_head_info_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_head_info ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::get_head_info_result< detail::max_hash_size, detail::max_hash_size > res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline int32_t apply_block( const block& b )
{
   koinos::chain::apply_block_arguments<
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_address_size,
      detail::max_proposal_length,
      detail::max_hash_size,
      detail::max_transaction_length,
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_nonce_size,
      detail::max_hash_size,
      detail::max_address_size,
      detail::max_address_size,
      detail::max_operation_length,
      detail::max_address_size,
      detail::max_contract_size,
      detail::max_contract_size,
      detail::max_address_size,
      detail::max_argument_size,
      detail::max_argument_size,
      detail::max_address_size,
      detail::max_signatures_length,
      detail::max_signature_size,
      detail::max_signature_size > args;
   args.mutable_block() = b;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   return invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::apply_block ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );
}

inline int32_t apply_transaction( const transaction& t )
{
   koinos::chain::apply_transaction_arguments<
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_nonce_size,
      detail::max_hash_size,
      detail::max_address_size,
      detail::max_address_size,
      detail::max_operation_length,
      detail::max_address_size,
      detail::max_contract_size,
      detail::max_contract_size,
      detail::max_address_size,
      detail::max_argument_size,
      detail::max_argument_size,
      detail::max_address_size,
      detail::max_signatures_length,
      detail::max_signature_size > args;
   args.mutable_transaction() = t;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   return invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::apply_transaction ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );
}

inline int32_t apply_upload_contract_operation( const upload_contract_operation& o )
{
   koinos::chain::apply_upload_contract_operation_arguments<
      detail::max_hash_size,
      detail::max_contract_size,
      detail::max_contract_size  > args;
   args.mutable_op() = o;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   return invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::apply_upload_contract_operation ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );
}

inline int32_t apply_call_contract_operation( const call_contract_operation& o )
{
   koinos::chain::apply_call_contract_operation_arguments<
      detail::max_hash_size,
      detail::max_argument_size > args;
   args.mutable_op() = o;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   return invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::apply_call_contract_operation ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );
}

inline int32_t apply_set_system_call_operation( const set_system_call_operation& o )
{
   koinos::chain::apply_set_system_call_operation_arguments< detail::max_argument_size > args;
   args.mutable_op() = o;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   return invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::apply_set_system_call_operation ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );
}

inline int32_t apply_set_system_contract_operation( const set_system_contract_operation& o )
{
   koinos::chain::apply_set_system_contract_operation_arguments< detail::max_address_size > args;
   args.mutable_op() = o;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   return invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::apply_set_system_contract_operation ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );
}

// System Helpers

inline bool process_block_signature( const std::string& digest, const block_header& header, const std::string& sig )
{
   koinos::chain::process_block_signature_arguments<
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_hash_size,
      detail::max_address_size,
      detail::max_proposal_length,
      detail::max_hash_size,
      detail::max_signature_size > args;

   args.mutable_digest().set( reinterpret_cast< const uint8_t* >( digest.data() ), digest.size() );
   args.mutable_header() = header;
   args.mutable_signature().set( reinterpret_cast< const uint8_t* >( sig.data() ), sig.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::process_block_signature ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::process_block_signature_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline value_type get_transaction_field( const std::string& field )
{
   koinos::chain::get_transaction_field_arguments< detail::max_field_name_length > args;
   args.mutable_field().set( field.data(), field.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_transaction_field ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::get_transaction_field_result< detail::max_field_size, detail::max_field_size > res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline value_type get_block_field( const std::string& field )
{
   koinos::chain::get_block_field_arguments< detail::max_field_name_length > args;
   args.mutable_field().set( field.data(), field.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_block_field ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::get_block_field_result< detail::max_field_size, detail::max_field_size > res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline uint64_t get_last_irreversible_block()
{
   koinos::chain::get_last_irreversible_block_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_last_irreversible_block ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::get_last_irreversible_block_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline std::string get_account_nonce( const std::string& account )
{
   koinos::chain::get_account_nonce_arguments< detail::max_address_size > args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_account_nonce ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::get_account_nonce_result< detail::max_nonce_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_const() ), res.get_value().get_length() );
}

inline bool check_system_authority()
{
   koinos::chain::check_system_authority_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::check_system_authority ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::check_system_authority_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

// Resource Subsystem

inline uint64_t get_account_rc( const std::string& account )
{
   koinos::chain::get_account_rc_arguments< detail::max_hash_size > args;
   args.mutable_account().set( reinterpret_cast< const uint8_t* >( account.data() ), account.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_account_rc ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::get_account_rc_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

// TODO: consume_account_rc

// TODO: get_resource_limits

// TODO: consume_block_resources

// Database

namespace detail {

inline void put_object( const object_space& space, const std::string& key, const std::string& obj )
{
   if ( key.size() > detail::max_key_size )
   {
      revert( "key size exceeds max size of " + std::to_string( detail::max_key_size ) );
   }

   put_object_arguments args;
   args.mutable_space() = space;
   args.mutable_key().set( reinterpret_cast< const uint8_t* >( key.data() ), key.size() );
   args.mutable_obj().set( reinterpret_cast< const uint8_t* >( obj.data() ), obj.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::put_object ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   if ( retval )
   {
      koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }
}

inline std::string get_object( const object_space& space, const std::string& key, uint32_t object_size_hint = 0 )
{
   if ( key.size() > detail::max_key_size )
   {
      revert( "key size exceeds max size of " + std::to_string( detail::max_key_size ) );
   }

   get_object_arguments args;
   args.mutable_space() = space;
   args.mutable_key().set( reinterpret_cast< const uint8_t* >( key.data() ), key.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_object ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::get_object_result< detail::max_argument_size, detail::max_key_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_value().get_const() ), res.get_value().get_value().get_length() );
}

} // detail

template< typename T >
void put_object( const object_space& space, const std::string& key, const T& value )
{
   std::array< uint8_t, detail::max_argument_size > buf;
   koinos::write_buffer buffer( buf.data(), buf.size() );
   value.serialize( buffer );
   detail::put_object( space, key, std::string( reinterpret_cast< char* >( buffer.data() ), buffer.get_size() ) );
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

inline void remove_object( const object_space& space, const std::string& key )
{
   if ( key.size() > detail::max_key_size )
   {
      revert( "key size exceeds max size of " + std::to_string( detail::max_key_size ) );
   }

   remove_object_arguments args;
   args.mutable_space() = space;
   args.mutable_key().set( reinterpret_cast< const uint8_t* >( key.data() ), key.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::remove_object ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   if ( retval )
   {
      koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }
}

inline std::string get_next_object( const object_space& space, const std::string& key )
{
   get_next_object_arguments args;
   args.mutable_space() = space;
   args.mutable_key().set( reinterpret_cast< const uint8_t* >( key.data() ), key.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_next_object ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::get_next_object_result< detail::max_argument_size, detail::max_key_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_value().get_const() ), res.get_value().get_value().get_length() );
}

inline std::string get_prev_object( const object_space& space, const std::string& key )
{
   get_prev_object_arguments args;
   args.mutable_space() = space;
   args.mutable_key().set( reinterpret_cast< const uint8_t* >( key.data() ), key.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_prev_object ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::get_prev_object_result< detail::max_argument_size, detail::max_key_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_value().get_const() ), res.get_value().get_value().get_length() );
}

// Logging

inline void log( const std::string& s )
{
   koinos::chain::log_arguments< detail::max_argument_size > args;
   args.mutable_message() = s.c_str();

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::log ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   if ( retval )
   {
      koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }
}

template< typename T >
inline void event( const std::string& name, const T& data, const std::vector< std::string >& impacted = {} )
{
   if ( impacted.size() > detail::max_impacted_size )
   {
      revert( "impacted size exceeds max size of " + std::to_string( detail::max_impacted_size ) );
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

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::event ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   if ( retval )
   {
      koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }
}

// Cryptography

inline std::string hash( uint64_t code, const std::string& obj, uint64_t size = 0 )
{
   koinos::chain::hash_arguments< detail::max_argument_size > args;
   args.mutable_code() = code;
   args.mutable_obj().set( reinterpret_cast< const uint8_t* >( obj.data() ), obj.size() );
   args.mutable_size() = size;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::hash ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::hash_result< detail::max_hash_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_const() ), res.get_value().get_length() );
}

inline std::string recover_public_key( const std::string& signature, const std::string& digest, koinos::chain::dsa algo = koinos::chain::dsa::ecdsa_secp256k1, bool compressed = true )
{
   koinos::chain::recover_public_key_arguments< detail::max_hash_size, detail::max_hash_size > args;
   args.set_type( algo );
   args.mutable_digest().set( reinterpret_cast< const uint8_t* >( digest.data() ), digest.size() );
   args.mutable_signature().set( reinterpret_cast< const uint8_t* >( signature.data() ), signature.size() );
   args.set_compressed( compressed );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::recover_public_key ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::recover_public_key_result< detail::max_hash_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_const() ), res.get_value().get_length() );
}

inline bool verify_merkle_root( const std::string& root, const std::vector< std::string >& hashes )
{
   koinos::chain::verify_merkle_root_arguments<
      detail::max_hash_size,
      detail::max_hashes_length,
      detail::max_hash_size > args;

   args.mutable_root().set( reinterpret_cast< const uint8_t* >( root.data() ), root.size() );
   for ( const auto& hash : hashes )
   {
      EmbeddedProto::FieldBytes< detail::max_hash_size > h;
      h.set( reinterpret_cast< const uint8_t* >( hash.data() ), hash.size() );
      args.add_hashes( h );
   }

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::verify_merkle_root ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::verify_merkle_root_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline bool verify_signature( chain::dsa type, const std::string& public_key, const std::string& digest, const std::string& signature, bool compressed = true )
{
   koinos::chain::verify_signature_arguments<
      detail::max_public_key_size,
      detail::max_signature_size,
      detail::max_hash_size > args;

   args.set_type( type );
   args.mutable_public_key().set( reinterpret_cast< const uint8_t* >( public_key.data() ), public_key.size() );
   args.mutable_digest().set( reinterpret_cast< const uint8_t* >( digest.data() ), digest.size() );
   args.mutable_signature().set( reinterpret_cast< const uint8_t* >( signature.data() ), signature.size() );
   args.set_compressed( compressed );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::verify_signature ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::verify_signature_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

inline bool verify_vrf_proof( chain::dsa type, const std::string& public_key, const std::string& proof, const std::string& hash, const std::string& message )
{
   koinos::chain::verify_vrf_proof_arguments<
      detail::max_public_key_size,
      detail::max_signature_size,
      detail::max_hash_size,
      detail::max_argument_size > args;

   args.set_type( type );
   args.mutable_public_key().set( reinterpret_cast< const uint8_t* >( public_key.data() ), public_key.size() );
   args.mutable_proof().set( reinterpret_cast< const uint8_t* >( proof.data() ), proof.size() );
   args.mutable_hash().set( reinterpret_cast< const uint8_t* >( hash.data() ), hash.size() );
   args.mutable_message().set( reinterpret_cast< const uint8_t* >( message.data() ), message.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   uint32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::verify_vrf_proof ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::verify_vrf_proof_result res;
   res.deserialize( rdbuf );

   return res.get_value();
}

// Contract Management

inline std::pair< int32_t, result > call( const std::string& id, uint32_t entry_point, const std::string& arguments )
{
   koinos::chain::call_arguments< detail::max_hash_size, detail::max_argument_size > args;
   args.mutable_contract_id().set( reinterpret_cast< const uint8_t* >( id.data() ), id.size() );
   args.mutable_entry_point() = entry_point;
   args.mutable_args().set( reinterpret_cast< const uint8_t* >( arguments.data() ), arguments.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::call ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );
   koinos::chain::result< detail::max_argument_size, detail::max_argument_size > res;

   if ( retval )
   {
      res.mutable_error().deserialize( rdbuf );
   }
   else
   {
      koinos::chain::call_result< detail::max_argument_size > call_res;
      call_res.deserialize( rdbuf );
      res.mutable_object().set( call_res.get_value() );
   }

   return std::make_pair( retval, std::move( res ) );
}

inline std::pair< uint32_t, std::string > get_arguments()
{
   koinos::chain::get_arguments_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_arguments ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::get_arguments_result< detail::max_argument_size > res;
   res.deserialize( rdbuf );

   return std::make_pair( res.get_value().entry_point(), std::string( reinterpret_cast< const char* >( res.get_value().get_arguments().get_const() ), res.get_value().get_arguments().get_length() ) );
}

inline void exit( int32_t code, const result& r )
{
   exit_arguments args;
   args.set_code( code );
   args.mutable_res() = r;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::exit ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );
}

inline void exit( const ::EmbeddedProto::MessageInterface& msg )
{
   result r;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   msg.serialize( buffer );

   r.mutable_object().set( buffer.data(), buffer.get_size() );

   exit( 0, r );
}

inline void revert( const std::string& msg, int32_t code )
{
   result r;
   r.mutable_error().mutable_message().set( reinterpret_cast< const char* >( msg.data() ), msg.size() );
   code = std::max( static_cast< int32_t >( chain::error_code::reversion ), code );

   exit( code, r );
}

inline void revert( const std::string& msg, chain::error_code code )
{
   revert( msg, static_cast< int32_t >( code ) );
}

inline void fail( const std::string& msg, int32_t code )
{
   result r;
   r.mutable_error().mutable_message().set( reinterpret_cast< const char* >( msg.data() ), msg.size() );
   code = std::min( static_cast< int32_t >( chain::error_code::failure ), code );

   exit( code, r );
}

inline void fail( const std::string& msg, chain::error_code code )
{
   fail( msg, static_cast< int32_t >( code ) );
}

inline std::string get_contract_id()
{
   koinos::chain::get_contract_id_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_contract_id ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::get_contract_id_result< detail::max_hash_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_const() ), res.get_value().get_length() );
}

inline std::pair< std::string, koinos::chain::privilege > get_caller()
{
   koinos::chain::get_caller_arguments args;

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_caller ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::get_caller_result< detail::max_hash_size > res;
   res.deserialize( rdbuf );

   auto value = res.value();
   return std::make_pair( std::string( reinterpret_cast< const char* >( value.get_caller().get_const() ), value.get_caller().get_length() ), value.get_caller_privilege() );
}

inline bool check_authority( const std::string& account, const std::string& data = std::string() )
{
   koinos::chain::check_authority_arguments< detail::max_hash_size, detail::max_argument_size > args;
   args.set_type( koinos::chain::authorization_type::contract_call );
   args.mutable_account().set( reinterpret_cast< const uint8_t* >( account.data() ), account.size() );
   args.mutable_data().set( reinterpret_cast< const uint8_t* >( data.data() ), data.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::check_authority ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::chain::check_authority_result res;
   res.deserialize( rdbuf );

   return res.value();
}

inline std::string get_contract_name( const std::string& address )
{
   koinos::contracts::name_service::get_name_arguments< detail::max_address_size > args;
   args.mutable_address().set( reinterpret_cast< const uint8_t* >( address.data() ), address.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_contract_name ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::contracts::name_service::get_name_result< 32 > res;
   res.deserialize( rdbuf );

   return std::string( res.get_value().get_name().get_const(), res.get_value().get_name().get_length() );
}

inline std::string get_contract_address( const std::string& name )
{
   koinos::contracts::name_service::get_address_arguments< 32 > args;
   args.mutable_name().set( name.data(), name.size() );

   koinos::write_buffer buffer( detail::syscall_buffer.data(), detail::syscall_buffer.size() );
   args.serialize( buffer );

   uint32_t bytes_written = 0;

   int32_t retval = invoke_system_call(
      std::underlying_type_t< koinos::chain::system_call_id >( koinos::chain::system_call_id::get_contract_address ),
      reinterpret_cast< char* >( detail::syscall_buffer.data() ),
      std::size( detail::syscall_buffer ),
      reinterpret_cast< char* >( buffer.data() ),
      buffer.get_size(),
      &bytes_written
   );

   koinos::read_buffer rdbuf( detail::syscall_buffer.data(), bytes_written );

   if ( retval )
   {
      result res;
      res.mutable_error().deserialize( rdbuf );
      exit( retval, res );
   }

   koinos::contracts::name_service::get_address_result< detail::max_address_size > res;
   res.deserialize( rdbuf );

   return std::string( reinterpret_cast< const char* >( res.get_value().get_address().get_const() ), res.get_value().get_address().get_length() );
}

} // koinos::system
