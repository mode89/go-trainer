project( go-trainer )
cmake_minimum_required( VERSION 2.8 )

list( APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" )

add_subdirectory( cmn )
list( APPEND CMAKE_PREFIX_PATH "${CMN_BINARY_DIR}" )

add_subdirectory( gnugo )
add_subdirectory( gtest )

add_subdirectory( opennn )
list( APPEND CMAKE_PREFIX_PATH "${OPENNN_BINARY_DIR}" )

add_subdirectory( trainer )
