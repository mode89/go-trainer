project( ANN )
cmake_minimum_required( VERSION 2.8 )

# Sources

    file( GLOB ANN_INCLUDE_FILES include/ann/*.h )
    source_group( "include" FILES ${ANN_INCLUDE_FILES} )

    file( GLOB ANN_SOURCE_FILES source/*.cpp )
    source_group( "source" FILES ${ANN_SOURCE_FILES} )

# Includes

    include_directories( include )

# Target

    add_library( ann ${ANN_SOURCE_FILES} ${ANN_INCLUDE_FILES} )

# Dependencies

    find_package( cmn CONFIG )
    target_link_libraries( ann ${CMN_LIBS} )
    include_directories( ${CMN_INCLUDE_DIRS} )

    find_package( ga CONFIG )
    include_directories( ${GA_INCLUDE_DIRS} )

# Tests

    add_subdirectory( tests )
