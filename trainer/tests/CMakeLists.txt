project( TRAINER_TESTS )

# Sources

    file( GLOB TRAINER_TESTS_SOURCE_FILES *.cpp *.h )
    add_executable( trainer-tests ${TRAINER_TESTS_SOURCE_FILES} )

# Dependencies

    target_link_libraries( trainer-tests trainer-lib )
    include_directories( .. )

    find_package( cmn REQUIRED )
    target_link_libraries( trainer-tests ${CMN_LIBS} )
    include_directories( ${CMN_INCLUDE_DIRS} )

    find_package( GTest REQUIRED )
    target_link_libraries( trainer-tests ${GTEST_LIBRARIES} )
    include_directories( ${GTEST_INCLUDE_DIRS} )
