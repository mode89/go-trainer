project( TRAINER )
cmake_minimum_required( VERSION 2.8 )

# Sources

    file( GLOB TEMP go/*.cpp go/*.h )
    source_group( "go" FILES ${TEMP} )
    list( APPEND TRAINER_SOURCE_FILES ${TEMP} )

    file( GLOB TEMP gnugo/*.cpp gnugo/*.h )
    source_group( "gnugo" FILES ${TEMP} )
    list( APPEND TRAINER_SOURCE_FILES ${TEMP} )

# Includes

    include_directories( . )

# Compiler options

    if ( UNIX )
        add_compile_options(
                -std=c++11
            )
    endif()

# Targets

    add_library( trainer-lib ${TRAINER_SOURCE_FILES} )
    add_executable( trainer main.cpp )

# Dependencies

    find_package( ann REQUIRED )
    target_link_libraries( trainer-lib ${ANN_LIBRARIES} )
    include_directories( ${ANN_INCLUDE_DIRS} )

    find_package( cmn REQUIRED )
    target_link_libraries( trainer-lib ${CMN_LIBS} )
    include_directories( ${CMN_INCLUDE_DIRS} )

    target_link_libraries( trainer trainer-lib )

# Build gnugo

    set( GNUGO_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/build-gnugo )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${GNUGO_BUILD_DIR} )
    execute_process(
        COMMAND ${CMAKE_COMMAND}
            -Wno-dev
            -DCMAKE_BUILD_TYPE=Release
            -DCMAKE_INSTALL_PREFIX=.
            -G ${CMAKE_GENERATOR}
            ${CMAKE_SOURCE_DIR}/gnugo
        WORKING_DIRECTORY ${GNUGO_BUILD_DIR} )
    execute_process(
        COMMAND ${CMAKE_COMMAND}
            --build ${GNUGO_BUILD_DIR}
            --target gnugo
            --config Release )
    execute_process(
        COMMAND ${CMAKE_COMMAND}
            --build ${GNUGO_BUILD_DIR}
            --target install
            --config Release )
    add_definitions( -DGNUGO_EXE="${GNUGO_BUILD_DIR}/bin/gnugo.exe" )

# Tests

    add_subdirectory( tests )
