cmake_minimum_required(VERSION 3.0)
project(newton)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE Debug)

add_library(newton
        src/newton.cpp
        src/basic_entity.cpp
        )

target_include_directories (newton PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(newton LINK_PUBLIC
        common
        )

