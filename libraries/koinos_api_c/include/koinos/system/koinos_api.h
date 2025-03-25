#pragma once

#include <stdint.h>
#include <stdbool.h>

#define KOINOS_IMPORT \
   __attribute__((visibility ("default")))
#define KOINOS_EXPORT \
   __attribute__((visibility ("default")))

KOINOS_IMPORT int32_t invoke_thunk( uint32_t tid, char* ret_ptr, uint32_t ret_len, const char* arg_ptr, uint32_t arg_len, uint32_t* bytes_written );
KOINOS_IMPORT int32_t invoke_system_call( uint32_t xid, char* ret_ptr, uint32_t ret_len, const char* arg_ptr, uint32_t arg_len, uint32_t* bytes_written );

KOINOS_IMPORT int32_t koinos_get_caller( char* ret_ptr, uint32_t* ret_len );
KOINOS_IMPORT int32_t koinos_get_object( uint32_t id, const char* key_ptr, uint32_t key_len, char* ret_ptr, uint32_t* ret_len );
KOINOS_IMPORT int32_t koinos_put_object( uint32_t id, const char* key_ptr, uint32_t key_len, const char* value_ptr, uint32_t value_len );
KOINOS_IMPORT int32_t koinos_check_authority( const char* account_ptr, uint32_t account_len, const char* data_ptr, uint32_t data_len, bool* value );
KOINOS_IMPORT int32_t koinos_log( const char* msg_ptr, uint32_t msg_len );
KOINOS_IMPORT int32_t koinos_get_arguments( uint32_t* entry_point, char* args_ptr, uint32_t* args_len );

KOINOS_IMPORT
__attribute__((__noreturn__))
void koinos_exit( int32_t code, const char* res_bytes, uint32_t res_len );

/* We cannot assume libc NULL is available, since koinos_api lives below libc. */
/* So we simply define our own NULL constant */

#define KOINOS_NULL ((void*) 0)
