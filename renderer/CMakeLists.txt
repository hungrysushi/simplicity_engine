cmake_minimum_required(VERSION 3.0)
project(renderer)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE Debug)

add_library(renderer
        src/renderer.cpp
        src/shader.cpp
        src/images.cpp
        )

find_package(PNG REQUIRED)

target_include_directories (renderer PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${PNG_INCLUDE_DIR})

target_link_libraries(renderer LINK_PUBLIC
        glad
        common
        ${PNG_LIBRARY}
        )

