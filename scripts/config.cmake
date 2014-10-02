# Using add_compile_options() requires
cmake_minimum_required( VERSION 3.0 )

# Setup common packages search path

set( CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR} )

# Obtain GCC version
if( CMAKE_COMPILER_IS_GNUCXX )
    execute_process( COMMAND g++ -dumpversion OUTPUT_VARIABLE CMN_GXX_VERSION )
endif()

# Static link standard libs
if( CMN_STATIC_LINK_STD_LIBS )
    if ( MINGW )
        set( CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++" )
    endif()
endif()

# Enable C++11
if( CMN_ENABLE_CXX11 )
    if( MINGW )
        if( ( CMN_GXX_VERSION VERSION_GREATER "4.7.0" ) OR ( CMN_GXX_VERSION VERSION_EQUAL "4.7.0" ) )
            set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11" )
        else()
            message( WARNING "CMN_CXX11_ENABLED is set but C++11 specification is not supported." )
        endif()
    endif()
endif()

# Define _VARIADIC_MAX preprocessor variable
if( CMN_MSVC_DEFINE_VARIADIC_MAX )
    if( MSVC )
        add_definitions( /D _VARIADIC_MAX=${CMN_MSVC_DEFINE_VARIADIC_MAX} )
    endif()
endif()

# Enable multithreaded compiling
if( CMN_MULTITHREADED_BUILD )
    if( MSVC )
        set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP" )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP" )
    endif()
endif()

# Enable additional warnings
if( CMN_MORE_WARNINGS )
    if( MSVC )
        add_compile_options(
            /Wall       # Enable all warnings
            /WX         # Treat all compiler warnings as errors

            # Disabling specific warnings
            /wd4061     # Enumerator 'value' in switch of enum 'enum' is not explicitly handled by a case label
            /wd4062     # Enumerator 'value' in switch of enum 'enum' is not handled
            /wd4100     # Unreferenced formal parameter
            /wd4350     # behavior change: 'member1' called instead of 'member2'
            /wd4365     # '=' : conversion from 'type1' to 'type2', signed/unsigned mismatch
            /wd4514     # Unreferenced inline function has been removed
            /wd4571     # catch(...) semantics changed since VC++ 7.1; structured exceptions are no longer caught
            /wd4640     # Construction of local static object is not threa-safe
            /wd4668     # 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
            /wd4710     # Function not inlined
            /wd4711     # Function 'function' selected for inline expansion
            /wd4820     # 'bytes' bytes padding added after construct 'member_name'
            /wd4826     # Conversion from 'type1' to 'type2' is sign-extended.
        )
    elseif( MINGW )
        add_compile_options(
            -Wall       # Enable most of the warnings
            -Wextra     # Enable extra warnings
            -Werror     # Treat all compiler warnings as errors

            # Disabling specific warnings
            -Wno-sequence-point             # Violations of sequence point rules
            -Wno-switch                     # Enumeration value not handled in switch
            -Wno-unknown-pragmas            # Unrecognized #pragma
            -Wno-unused-but-set-variable    # Local variable is assigned to, but otherwise not used
            -Wno-unused-parameter           # Unreferenced formal parameter
        )
    endif()
endif()

# Macroses

macro(target_precompiled_header target precHeader precSource)
    if (MSVC_IDE)
        set_target_properties(${target} PROPERTIES COMPILE_FLAGS "/Yu${precHeader}")
        set_source_files_properties(${precSource} PROPERTIES COMPILE_FLAGS "/Yc${precHeader}")
    endif()
endmacro(target_precompiled_header)

function( target_dependencies targetName )
    math( EXPR PACKC "${ARGC} - 1" )
    foreach( ARGN RANGE 1 ${PACKC} )
        set( PACKAGE ${ARGV${ARGN}} )
        find_package( ${PACKAGE} CONFIG )
        string( TOUPPER ${PACKAGE} PACKAGE )
        target_link_libraries( ${targetName} ${${PACKAGE}_LIBS} )
        include_directories( ${${PACKAGE}_INCLUDE_DIRS} )
    endforeach()
endfunction()
