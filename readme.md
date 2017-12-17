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

The test binary is located at `build/test/testengine`.

For convenience, tests can be automatically run with ctest using
```
make test
```
If any fail, the actual gtest executable can be run with
```
make run_gtest
```
which will provide more details about what exactly is failing.


### To do

- Initial Setup
  - ~~cmake files~~
- ~~Integrate gtest~~
- Renderer
  - ~~Set up GLFW and GLAD~~
  - ~~Basic shaders~~
  - Basic methods to draw triangles and rectangles
- ~~Input~~
  - ~~Callbacks~~
- World representation
  - ~~Entities~~
  - Behaviors
- Load levels from file
- Logging
- Audio


Regarding the event callbacks, I went back and forth about making it generic so anyone can define events or having all events be enumerated in the event handler. For now, the second option seems better. Callbacks/event handling from outside should be designed outside.

Asset and memory management should happen in a separate component. Raw pointers can be passed around, but their entire lifecycle should be managed from this component.

#### Stepping stones

- Bring up a window
- Draw triangle on screen
- Process keyboard input
- Move triangle with keyboard
- Add texture to triangle
- Draw items on screen from a level file
