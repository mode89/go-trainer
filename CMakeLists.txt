project( CMN )
cmake_minimum_required( VERSION 2.8 )

# Source files

    file( GLOB CMN_SOURCE_FILES source/*.cpp )
    source_group( "source" FILES ${CMN_SOURCE_FILES} )

    file( GLOB CMN_HEADER_FILES include/cmn/*.h )
    source_group( "include" FILES ${CMN_HEADER_FILES} )

# Target

    add_library( cmn ${CMN_SOURCE_FILES} ${CMN_HEADER_FILES} )
    include_directories( include )
