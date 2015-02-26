project( go-trainer )
cmake_minimum_required( VERSION 2.8 )

list( APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" )

add_subdirectory( cmn )
list( APPEND CMAKE_PREFIX_PATH "${CMN_BINARY_DIR}" )

add_subdirectory( gnugo )

add_subdirectory( gtest )
set( GTEST_ROOT "${CMAKE_SOURCE_DIR}/gtest" )
list( APPEND CMAKE_PREFIX_PATH "${gtest_BINARY_DIR}" )

add_subdirectory( trainer )
