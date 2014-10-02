project( ANN )
cmake_minimum_required( VERSION 2.8 )

file( GLOB ANN_INCLUDE_FILES include/ann/*.h )
source_group( "include" FILES ${ANN_INCLUDE_FILES} )

file( GLOB ANN_SOURCE_FILES source/*.cpp )
source_group( "source" FILES ${ANN_SOURCE_FILES} )

add_library( ann ${ANN_SOURCE_FILES} ${ANN_INCLUDE_FILES} )

include_directories( include )

find_package( cmn CONFIG )
target_link_libraries( ann ${CMN_LIBS} )
include_directories( ${CMN_INCLUDE_DIRS} )

find_package( ga CONFIG )
include_directories( ${GA_INCLUDE_DIRS} )

add_subdirectory( tests )
