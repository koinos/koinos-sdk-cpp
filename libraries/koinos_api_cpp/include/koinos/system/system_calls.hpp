#include <koinos/pack/rt/binary.hpp>
#include <koinos/pack/classes.hpp>
#include <koinos/pack/system_call_ids.hpp>

namespace koinos::system {

void print( const std::string& s );
types::variable_blob get_contract_args();

bool verify_block_sig( const types::variable_blob& sig_data, const types::multihash_type& digest );
bool verify_merkle_root( const types::multihash_type& root, const std::vector< types::multihash_type >& hashes );

void apply_block( const std::vector< types::system::block_part >& p, bool enable_check_passive_data, bool enable_check_block_signature, bool enabled_check_transaction_signatures );
void apply_transaction( const types::variable_blob& tx_blob );
void apply_reserved_operation( const types::protocol::reserved_operation& o );
void apply_upload_contract_operation( const types::protocol::create_system_contract_operation& o );
void apply_execute_contract_operation( const types::protocol::contract_call_operation& op );
void apply_set_system_call_operation( const types::protocol::set_system_call_operation& op );

bool db_put_object( const types::uint256& space, const types::uint256& key, const types::variable_blob& obj );
types::variable_blob db_get_object( const types::uint256& space, const types::uint256& key, int32_t object_size_hint = -1 );
types::variable_blob db_get_next_object( const types::uint256& space, const types::uint256& key, int32_t object_size_hint = -1 );
types::variable_blob db_get_prev_object( const types::uint256& space, const types::uint256& key, int32_t object_size_hint = -1 );

types::variable_blob execute_contract( const types::contract_id_type& contract_id, uint32_t entry_point, const types::variable_blob& args );

uint32_t get_contract_args_size();
types::variable_blob get_contract_args();

void set_contract_return( const types::variable_blob& ret );

types::system::head_info get_head_info();

types::multihash_type hash( uint64_t code, const types::variable_blob& obj, uint64_t size = 0 );


} // koinos::system
