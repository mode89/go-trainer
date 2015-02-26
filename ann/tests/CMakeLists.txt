project( ANN_TESTS )

# Target

    file( GLOB ANN_TESTS_SOURCE_FILES *.cpp )
    add_executable( ann-tests ${ANN_TESTS_SOURCE_FILES} )
    target_link_libraries( ann-tests ann )

# Dependencies

    find_package( gtest CONFIG )
    target_link_libraries( ann-tests ${GTEST_LIBS} )
    include_directories( ${GTEST_INCLUDE_DIRS} )
