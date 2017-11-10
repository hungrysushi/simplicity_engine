
project(unit_tests)

# make the googletest modules available
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

enable_testing()

add_executable(testengine
        test_main.cpp
        # include test files here
        simplicity_tests.cpp
        )

# Link googletest and googlemock
target_link_libraries(testengine
        gtest
        gmock
        )

# our modules to test
target_link_libraries(testengine
        simplicity_engine
        )

# run our tests
add_test(test-simplicity-engine testengine)
