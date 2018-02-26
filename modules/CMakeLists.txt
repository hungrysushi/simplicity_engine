 
# windowing
add_subdirectory(glfw)
include_directories(glfw/include)

# hardware specific opengl support
# generate it with this line in the glad directory:
#       python -m glad --generator c --no-loader --out-path ../glad_generated
add_subdirectory(glad_generated)

# make the googletest modules available
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

# memory pool
add_subdirectory(memory_pool)

# other 3rd party header-only files
include_directories(include)
