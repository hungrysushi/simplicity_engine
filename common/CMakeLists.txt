cmake_minimum_required(VERSION 3.0)
project(common)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE Debug)

add_library(common INTERFACE
        )

target_include_directories (common INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(common LINK_PUBLIC
        )

