 
# windowing
add_subdirectory(glfw)
include_directories(glfw/include)

# hardware specific opengl support
# generate it with this line in the glad directory:
#       python -m glad --generator c --no-loader --out-path ../glad_generated
add_subdirectory(glad_generated)

# other 3rd party header-only files
include_directories(include)
