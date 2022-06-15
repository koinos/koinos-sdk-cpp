
#include <koinos/system/koinos_api.h>
#include <koinos/system/system_call_ids.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-noreturn"
__attribute__((__noreturn__))
void koinos_exit( int32_t rval )
{
   // We are hand generating an exit_arguments message
   // Largest buffer is for exit code -1
   char *buf = {0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01};
   uint32_t bytes_written = 11;

   if ( rval == 0 )
      bytes_written = 0;
   if ( rval > 0 )
   {
      buf[1] = 0x01;
      bytes_written = 2;
   }

   invoke_system_call( KOINOS_SYSTEM_CALL_EXIT, KOINOS_NULL, 0, buf, bytes_written, &bytes_written );
}
#pragma GCC diagnostic pop
