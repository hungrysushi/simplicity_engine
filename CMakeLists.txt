cmake_minimum_required(VERSION 3.0)
project(simplicity_engine)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE Debug)

add_library(simplicity_engine
        src/simplicity.cpp)

target_include_directories (simplicity_engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(3rd_party)

