project( OPENNN )

file( GLOB OPENNN_SOURCE_FILES opennn/*.cpp )
add_library( opennn ${OPENNN_SOURCE_FILES} )

set( OPENNN_LIBRARIES opennn )
configure_file( OpenNNConfig.cmake.in
    ${PROJECT_BINARY_DIR}/OpenNNConfig.cmake )
