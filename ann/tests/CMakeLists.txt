project( ANN_TESTS )

# Target

    file( GLOB ANN_TESTS_SOURCE_FILES *.cpp )
    add_executable( ann-tests ${ANN_TESTS_SOURCE_FILES} )
    target_link_libraries( ann-tests ann )

# Dependencies

    find_package( GTest REQUIRED )
    target_link_libraries( ann-tests ${GTEST_LIBRARIES} )
    include_directories( ${GTEST_INCLUDE_DIRS} )
