#include <unistd.h>
#include <stdlib.h>

namespace __cxxabiv1 {
    struct __class_type_info {
        virtual void foo() {}
    } ti;
}

extern "C" {

void* __cxa_allocate_exception( size_t thrown_size )
{
   exit(EXIT_FAILURE);
}

void __cxa_throw( void* thrown_exception, struct type_info *tinfo, void (*dest)(void*))
{
   exit(EXIT_FAILURE);
}

} // extern "C"
