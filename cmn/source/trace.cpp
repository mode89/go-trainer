#include "cmn\trace.h"

#include <cstdarg>
#include <cstdio>
#include <iostream>

#if CMN_COMPILER_MSVC
    #include <windows.h>
    CMN_WARNING_DISABLE_MSVC( 4996 ) // Deprecated functions
#endif

namespace Cmn {

    void TraceMessage( const char * format, ... )
    {
        char message[ 4096 ];

        va_list args;
        va_start( args, format );
        vsprintf( message, format, args );
        va_end( args );

        std::cout << message;
    }

    void TraceError( const char * format, ... )
    {
        char message[ 4096 ];

        va_list args;
        va_start( args, format );
        vsprintf( message, format, args );
        va_end( args );

        std::cerr << message;
    }

} // namespace Trace
