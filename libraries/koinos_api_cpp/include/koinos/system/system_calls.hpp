#include <koinos/pack/rt/binary.hpp>
#include <koinos/pack/classes.hpp>
#include <koinos/pack/system_call_ids.hpp>

namespace koinos::system {

void print( const std::string& s );
variable_blob get_contract_args();

bool verify_block_signature( const variable_blob& sig, const multihash& digest );

void apply_block( const protocol::block& b );
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

chain::head_info get_head_info();

multihash hash( uint64_t code, const variable_blob& obj, uint64_t size = 0 );


} // koinos::system
