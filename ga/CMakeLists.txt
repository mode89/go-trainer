project( GA )
cmake_minimum_required( VERSION 2.8 )

include_directories( include )

add_subdirectory( tests )

configure_file( ga-config.cmake.in
    ${PROJECT_BINARY_DIR}/ga-config.cmake )
