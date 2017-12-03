
#define SHADER_DIR "../shaders/"

#include <iostream>

#include "simplicity/entity.h"
#include "simplicity/renderer_types.h"
#include "simplicity/shader.h"
#include "simplicity/simplicity.h"
#include "simplicity/world.h"
#include "simplicity/world_types.h"

/*
 * This serves as a functional demo of the features and is an example
 * workflow. As more features are added, they should also be added to
 * the demo in some way.
 */
int main()
{
        simplicity::Simplicity engine;

        //engine.Demo();
        engine.InitWindow(500, 500, "Demo");

        // set up the input handler
        // the default input handler with GLFW *must* be initialized after
        // InitWindow, because we need to give it the handle to the window
        // TODO consider moving this to InitWindow?
        engine.input_handler_.Initialize(engine.window_);

        // TODO this might be better wrapped inside a function in the engine
        // ie SetShader or something like that
        simplicity::Shader shader;
        shader.Initialize("../shaders/basic.vs", "../shaders/basic.fs");
        engine.renderer_.Initialize(shader);

        // create the world
        // again, maybe something better wrapped in an engine function, or just
        // go ahead and do it when initializing the engine, and then grab a
        // shared pointer to it
        // TODO
        simplicity::World world;

        // create entities
        // ex RendererError renderer_err = renderer_.CreateRectangle(&entity);
        simplicity::Entity entity("demo entity");
        simplicity::RendererError renderer_err = engine.renderer_.CreateRectangle(5.0, 5.0, 0.5, entity);

        // add entities to the world
        // ex WorldError world_err = world.AddEntity(entity);
        simplicity::WorldError world_err = world.AddEntity(entity);

        // Debug
        world.PrintWorld();

        // main loop
        while (engine.IsRunning()) {
                // update the world
                // note: in order to update any of the entity characteristics,
                // we will have to hold on to the objects.
                // The other way to give entities behaviors is by callbacks

                // render the world
                //engine.renderer_.DrawWorld(world);

                // process input
                engine.input_handler_.ProcessInput();
        }

        return 0;
}
