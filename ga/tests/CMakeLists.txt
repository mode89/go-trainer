project( GA_TESTS )

# Target

    file( GLOB GA_TESTS_SOURCE_FILES *.cpp )
    add_executable( ga-tests ${GA_TESTS_SOURCE_FILES} )

# Dependencies

    find_package( gtest CONFIG )
    target_link_libraries( ga-tests ${GTEST_LIBS} )
    include_directories( ${GTEST_INCLUDE_DIRS} )

    find_package( cmn CONFIG )
    target_link_libraries( ga-tests ${CMN_LIBS} )
    include_directories( ${CMN_INCLUDE_DIRS} )
