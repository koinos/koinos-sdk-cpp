
#include <koinos/system/koinos_api.h>
#include <koinos/system/system_call_ids.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-noreturn"
__attribute__((__noreturn__))
void koinos_exit( uint32_t rval )
{
   // We are hand generating an exit_contract_args message
   char rbuf[2];
   rbuf[0] = 0x08;
   rbuf[1] = ( rval == 0 ) ? 0x00 : 0x01;
   invoke_system_call( KOINOS_SYSTEM_CALL_EXIT_CONTRACT, KOINOS_NULL, 0, &rbuf, 2 );
}
#pragma GCC diagnostic pop
