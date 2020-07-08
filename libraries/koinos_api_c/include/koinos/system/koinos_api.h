#pragma once

#include <stdint.h>

#define KOINOS_IMPORT \
   __attribute__((visibility ("default")))
#define KOINOS_EXPORT \
   __attribute__((visibility ("default")))

KOINOS_IMPORT void invoke_thunk( uint32_t tid, uint8_t* ret_ptr, uint32_t ret_len, const uint8_t* arg_ptr, uint32_t arg_len );
KOINOS_IMPORT void invoke_system_call( uint32_t xid, uint8_t* ret_ptr, uint32_t ret_len, const uint8_t* arg_ptr, uint32_t arg_len );

__attribute__((__noreturn__))
void koinos_exit( uint32_t rval );

/* We cannot assume libc NULL is available, since koinos_api lives below libc. */
/* So we simply define our own NULL constant */

#define KOINOS_NULL ((void*) 0)
