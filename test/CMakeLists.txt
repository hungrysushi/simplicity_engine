
project(unit_tests)

add_executable(testengine
        test_main.cpp
        # include test files here
        simplicity_tests.cpp
        shader_tests.cpp
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
add_custom_target(run_gtest testengine)
add_dependencies(run_gtest testengine)
