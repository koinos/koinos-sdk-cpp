
#include <koinos/system/koinos_api.h>
#include <koinos/system/system_call_ids.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-noreturn"
__attribute__((__noreturn__))
void koinos_exit( uint32_t rval )
{
   uint8_t rbyte = (rval == 0) ? 0 : 1;
   invoke_system_call( KOINOS_SYSTEM_CALL_ID_exit_contract, KOINOS_NULL, 0, &rbyte, 1 );
}
#pragma GCC diagnostic pop
