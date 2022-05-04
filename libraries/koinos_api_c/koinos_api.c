
#include <koinos/system/koinos_api.h>
#include <koinos/system/system_call_ids.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-noreturn"
__attribute__((__noreturn__))
void koinos_exit( int32_t rval )
{
   // We are hand generating an exit_args message
   char rbuf[4];
   rbuf[0] = 0x0a;
   rbuf[1] = 0x02;
   rbuf[2] = 0x08;
   rbuf[3] = ( rval == 0 ) ? 0x00 : 0x01;
   invoke_system_call( KOINOS_SYSTEM_CALL_EXIT, KOINOS_NULL, 0, rbuf, 4 );
}
#pragma GCC diagnostic pop
