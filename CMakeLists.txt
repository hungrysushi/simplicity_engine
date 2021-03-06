cmake_minimum_required(VERSION 3.0)
project(simplicity_engine)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE Debug)

add_library(simplicity_engine
        src/simplicity.cpp
        # other engine sources should be added here
        src/entity.cpp
        src/global_events.cpp
        src/input_handler.cpp
        src/renderer.cpp
        src/resource_manager.cpp
        src/shader.cpp
        src/world.cpp
        )

target_include_directories (simplicity_engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(simplicity_engine LINK_PUBLIC
        glad
        glfw ${GLFW_LIBRARIES}
        memory_pool
        )

# 3rd party modules
add_subdirectory(modules)

# Unit tests
enable_testing()
add_subdirectory(test)

# Test executable
add_executable(simplicity_demo
        demo.cpp)
target_link_libraries(simplicity_demo LINK_PUBLIC
        simplicity_engine)
