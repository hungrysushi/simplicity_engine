cmake_minimum_required(VERSION 3.0)
project(simplicity_engine)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE Debug)

add_library(simplicity_engine
        src/simplicity.cpp
        # other engine sources should be added here
        src/entity.cpp
        src/renderer.cpp
        src/shader.cpp
        src/world.cpp
        )

target_include_directories (simplicity_engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(simplicity_engine LINK_PUBLIC
        glfw ${GLFW_LIBRARIES}
        glad)

# 3rd party modules
add_subdirectory(3rd_party)

# Unit tests
enable_testing()
add_subdirectory(test)

# Test executable
add_executable(simplicity_demo
        main.cpp)
target_link_libraries(simplicity_demo LINK_PUBLIC
        simplicity_engine)
