project( LS_TESTS )

# Sources

    file( GLOB LS_TESTS_SOURCE_FILES *.cpp *.h )
    add_executable( ls-tests ${LS_TESTS_SOURCE_FILES} )

# Dependencies

    target_link_libraries( ls-tests ls-lib )
    include_directories( .. )

    find_package( cmn CONFIG )
    target_link_libraries( ls-tests ${CMN_LIBS} )
    include_directories( ${CMN_INCLUDE_DIRS} )

    find_package( gtest CONFIG )
    target_link_libraries( ls-tests ${GTEST_LIBS} )
    include_directories( ${GTEST_INCLUDE_DIRS} )
