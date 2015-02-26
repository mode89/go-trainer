project( go-trainer )
cmake_minimum_required( VERSION 2.8 )

list( APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" )

add_subdirectory( cmn )
list( APPEND CMAKE_PREFIX_PATH "${CMN_BINARY_DIR}" )

add_subdirectory( ga )
list( APPEND CMAKE_PREFIX_PATH "${GA_BINARY_DIR}" )

add_subdirectory( ann )
list( APPEND CMAKE_PREFIX_PATH "${ANN_BINARY_DIR}" )

add_subdirectory( gnugo )

set( gtest_force_shared_crt ON CACHE BOOL "Build GTest with shared CRT" )
add_subdirectory( gtest )

add_subdirectory( trainer )
