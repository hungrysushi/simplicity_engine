
project(glad_generated)

add_library(glad
        src/glad.c)

target_include_directories(glad PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

# turn this on if we want to build a shared library
# set_property(TARGET glad PROPERTY POSITION_INDEPENDENT_CODE ON)
