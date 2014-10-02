#ifndef __CMN_TRACE_H__
#define __CMN_TRACE_H__

#include "cmn\platform.h"
#include <cstdint>
#include <stdexcept>

// Software breakpoint

#if CMN_DEBUG
    #if CMN_COMPILER_MSVC
        #define CMN_DEBUG_BREAK()     __debugbreak()
    #elif CMN_COMPILER_MINGW
        #define CMN_DEBUG_BREAK()     asm("int $3")
    #endif // Determine the compiler
#else
    #define CMN_DEBUG_BREAK()
#endif

// Failing

#if CMN_DEBUG
    #define CMN_FAIL_MSG( ... ) \
        Cmn::TraceError( "%s(%d) : Failed : ", __FILE__, __LINE__ ); \
        Cmn::TraceError( __VA_ARGS__ ); \
        Cmn::TraceError( "\n" ); \
        CMN_DEBUG_BREAK()

    #define CMN_FAIL() \
        Cmn::TraceError( "%s(%d) : Failed", __FILE__, __LINE__ ); \
        Cmn::TraceError( "\n" ); \
        CMN_DEBUG_BREAK()
#else
    #define CMN_FAIL_MSG( ... )
    #define CMN_FAIL()
#endif // CMN_DEBUG

// Assertion

#if CMN_DEBUG
    #define CMN_ASSERT( expr ) \
        if ( !( expr ) ) \
        { \
            Cmn::TraceError( "%s(%d) : Assertion failed : %s", __FILE__, __LINE__, #expr ); \
            Cmn::TraceError( "\n" ); \
            CMN_DEBUG_BREAK(); \
        }

    #define CMN_ASSERT_MSG( expr, ... ) \
        if ( !( expr ) ) \
        { \
            Cmn::TraceError( "%s(%d) : Assertion failed : %s : ", __FILE__, __LINE__, #expr ); \
            Cmn::TraceError( __VA_ARGS__ ); \
            Cmn::TraceError( "\n" ); \
            CMN_DEBUG_BREAK(); \
        }

    #define CMN_ASSERT_AND( expr, var ) \
        var = var && ( expr ); \
        if ( !var ) \
        { \
            Cmn::TraceError( "%s(%d) : Assertion failed : %s", __FILE__, __LINE__, #expr ); \
            Cmn::TraceError( "\n" ); \
            CMN_DEBUG_BREAK(); \
        }
#else
    #define CMN_ASSERT( expr )
    #define CMN_ASSERT_MSG( expr, ... )
    #define CMN_ASSERT_AND( expr, var )
#endif // CMN_DEBUG

// Messages

#define CMN_MSG( ... ) \
    Cmn::TraceMessage( __VA_ARGS__ ); \
    Cmn::TraceMessage( "\n" )

#define CMN_ERR( ... ) \
    Cmn::TraceError( __VA_ARGS__ ); \
    Cmn::TraceError( "\n" )

// Exceptions

#define CMN_THROW( type ) \
    CMN_DEBUG_BREAK(); \
    throw type

#define CMN_THROW_IF( expr, type ) \
    if ( expr ) \
    { \
        CMN_THROW( type ); \
    }

namespace Cmn {

    // Subroutine to show a formatted message

    void TraceMessage( const char * format, ... );

    void TraceError( const char * format, ... );

} // namespace Cmn

#endif // __CMN_TRACE_H__
