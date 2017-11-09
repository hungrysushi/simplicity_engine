# Simplicity Engine

This is a focused rewrite of an earlier project.

The main feature goals are as follows:
- Provide a simple setup for any kind of 2D game, but focused on platformers
- Avoid having too much logic and configuration
- Support a simple level format
- Edit levels through a standalone level editor (tentative)
- Demo clone of Super Mario Bros. 1-1

Other goals:
- Clean and consistent code style
- Unit testing as much as possible

### Testing

Put gtest files in the tests/ folder. Add each new file to the source list for add_executable.

### To do

- Initial Setup
        - cmake files
- Integrate gtest
- Renderer
        - Set up GLFW and GLAD
        - Basic shaders
        - Basic methods to draw triangles and rectangles
- Input
        - Callbacks
- World representation
        - Entities
        - Behaviors
- Load levels from file
- Audio

