#ifndef __CMN_PLATFORM_H__
#define __CMN_PLATFORM_H__

#if defined( WIN32 ) || defined( __MINGW32__ )
    #define CMN_WIN32	1
#endif // defined( WIN32 ) || defined( __MINGW32__ )

#if defined( __MINGW32__ ) || defined( __MINGW64__ )
    #define CMN_COMPILER_MINGW	1
#endif // defined( __MINGW32__ ) || defined( __MINGW64__ )

#if defined( _MSC_VER )
    #define CMN_COMPILER_MSVC	1
#endif // defined( _MSC_VER )

#if defined( NDEBUG )
    #define CMN_NDEBUG 1
#else
    #define CMN_DEBUG 1
#endif // defined( NDEBUG )

// Thread local storage
#if defined( CMN_COMPILER_MSVC )
    #define CMN_THREAD_LOCAL   __declspec( thread )
#elif defined( CMN_COMPILER_MINGW )
    #define CMN_THREAD_LOCAL   __thread
#endif

// Some compilers doesn't support noexcept() operator
#if defined( CMN_COMPILER_MSVC )
    #define CMN_NOEXCEPT( val )
#elif defined( CMN_COMPILER_MINGW )
    #define CMN_NOEXCEPT( val ) noexcept( val )
#endif

// If variable is unused use this macro
#define CMN_UNUSED( var )  ( ( void ) var )

#define CMN_STRINGIFY( val ) #val
#define CMN_STRINGIFY2( val ) CMN_STRINGIFY( val )

// Overriding pragma
#if defined( CMN_COMPILER_MSVC )
    #define CMN_PRAGMA( dirv )     __pragma( dirv )
#elif defined( CMN_COMPILER_MINGW )
    #define CMN_PRAGMA( dirv )     _Pragma( #dirv )
#endif

// Controlling warnings
#if defined( CMN_COMPILER_MSVC )
    #define CMN_WARNING_PUSH                   CMN_PRAGMA( warning( push ) )
    #define CMN_WARNING_POP                    CMN_PRAGMA( warning( pop ) )

    #define CMN_WARNING_DEFAULT_MSVC( warn )   CMN_PRAGMA( warning( default : warn ) )
    #define CMN_WARNING_DISABLE_MSVC( warn )   CMN_PRAGMA( warning( disable : warn ) )
    #define CMN_WARNING_DISABLE_GCC( warn )
#elif defined( CMN_COMPILER_MINGW )
    #define CMN_WARNING_PUSH                   CMN_PRAGMA( GCC diagnostic push )
    #define CMN_WARNING_POP                    CMN_PRAGMA( GCC diagnostic pop )

    #define CMN_WARNING_DEFAULT_MSVC( warn )
    #define CMN_WARNING_DISABLE_MSVC( warn )
    #define CMN_WARNING_DISABLE_GCC( warn )    CMN_PRAGMA( GCC diagnostic ignored "-W" #warn )
#endif

#endif // __CMN_PLATFORM_H__
