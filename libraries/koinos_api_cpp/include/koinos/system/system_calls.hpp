#include <koinos/pack/rt/binary.hpp>
#include <koinos/pack/classes.hpp>
#include <koinos/pack/system_call_ids.hpp>

namespace koinos::system {

using chain::account_type;

void print( const std::string& s );

bool verify_block_signature( const variable_blob& sig, const multihash& digest );

void apply_block( const protocol::block& b, bool enable_check_passive_data, bool enable_check_block_signature, bool enabled_check_transaction_signatures );
void apply_transaction( const protocol::transaction& t );
void apply_reserved_operation( const protocol::reserved_operation& o );
void apply_upload_contract_operation( const protocol::create_system_contract_operation& o );
void apply_execute_contract_operation( const protocol::contract_call_operation& op );
void apply_set_system_call_operation( const protocol::set_system_call_operation& op );

bool db_put_object( const uint256& space, const uint256& key, const variable_blob& obj );
variable_blob db_get_object( const uint256& space, const uint256& key, int32_t object_size_hint = -1 );
variable_blob db_get_next_object( const uint256& space, const uint256& key, int32_t object_size_hint = -1 );
variable_blob db_get_prev_object( const uint256& space, const uint256& key, int32_t object_size_hint = -1 );

variable_blob execute_contract( const contract_id_type& contract_id, uint32_t entry_point, const variable_blob& args );

uint32_t get_contract_args_size();
variable_blob get_contract_args();
void set_contract_return( const variable_blob& ret );

void exit_contract( uint8_t exit_code );
chain::head_info get_head_info();

multihash hash( uint64_t code, const variable_blob& obj, uint64_t size = 0 );
bool verify_merkle_root( const multihash& root, const std::vector< multihash >& hashes );

account_type get_transaction_payer( const protocol::transaction& trx );
uint128 get_max_account_resources( const account_type& account );
uint128 get_transaction_resource_limit( const protocol::transaction& trx );

block_height_type get_last_irreversible_block();

account_type get_caller();

void require_authority( const account_type& account );
variable_blob get_transaction_signature();

} // koinos::system
