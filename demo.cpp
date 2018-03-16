/*
 * This serves as a functional demo of the features and is an example
 * workflow. As more features are added, they should also be added to
 * the demo in some way.
 */

#define SHADER_DIR "../shaders/"

#include <iostream>
#include <string>

#include "simplicity/entity.h"
#include "simplicity/entity_types.h"
#include "simplicity/renderer_types.h"
#include "simplicity/resource_manager.h"
#include "simplicity/shader.h"
#include "simplicity/simplicity.h"
#include "simplicity/world.h"
#include "simplicity/world_types.h"

void CreateFloorBlocks();
void SetUpEvents(simplicity::Entity& entity);

simplicity::Simplicity engine;
simplicity::World world;
simplicity::ResourceManager resource_manager;

int main()
{
        engine.Initialize("Demo");

        // set up the input handler
        // the default input handler with GLFW *must* be initialized after
        // InitWindow, because we need to give it the handle to the window
        // TODO consider moving this to InitWindow?
        /* engine.input_handler_.Initialize(engine.window_); */
        
        // TODO this might be better wrapped inside a function in the engine
        // ie SetShader or something like that
        /* simplicity::Shader shader; */
        /* shader.Initialize("../shaders/basic.vs", "../shaders/basic.fs"); */
        /* engine.renderer_.Initialize(shader); */

        // create the world
        // again, maybe something better wrapped in an engine function, or just
        // go ahead and do it when initializing the engine, and then grab a
        // shared pointer to it
        // TODO
        world.background_color_ = { 93.0 / 255, 148.0 / 255, 251.0 / 255 };

        CreateFloorBlocks();

        // create entities
        // ex RendererError renderer_err = renderer_.CreateRectangle(&entity);
        simplicity::Entity entity("demo entity");
        simplicity::RendererError renderer_err = engine.renderer_.CreateRectangle(5.0, 5.0, 0.05, entity);
        entity.coords_.y = 250.0;

        // register input and event callbacks
        engine.input_handler_.RegisterInputEvent(simplicity::Event::kEscKeyPress, [&](){
                        std::cout << "Escape key pressed." << std::endl;
                        engine.CloseWindow();
                        });
        engine.input_handler_.RegisterInputEvent(simplicity::Event::kWKeyPress, [&](){
                        std::cout << "W key pressed." << std::endl;
                        entity.coords_.y += 13;
                        });
        engine.input_handler_.RegisterInputEvent(simplicity::Event::kAKeyPress, [&](){
                        std::cout << "A key pressed." << std::endl;
                        entity.coords_.x -= 10;
                        world.view_location_.x -= 10;
                        });
        engine.input_handler_.RegisterInputEvent(simplicity::Event::kSKeyPress, [&](){
                        std::cout << "S key pressed." << std::endl;
                        entity.coords_.y -= 10;
                        });
        engine.input_handler_.RegisterInputEvent(simplicity::Event::kDKeyPress, [&](){
                        std::cout << "D key pressed." << std::endl;
                        entity.coords_.x += 10;
                        world.view_location_.x += 10;
                        });

        // add entities to the world
        // ex WorldError world_err = world.AddEntity(entity);
        simplicity::WorldError world_err = world.AddEntity(entity);

        // set up common update events
        SetUpEvents(entity);

        // Debug
        /* world.PrintWorld(); */

        // main loop
        while (engine.IsRunning()) {
                // update the world
                // note: in order to update any of the entity characteristics,
                // we will have to hold on to the objects.
                // The other way to give entities behaviors is by callbacks

                // render the world
                engine.renderer_.DrawWorld(world);

                // process input
                engine.input_handler_.ProcessInput();

                world.UpdateWorld();
        }

        return 0;
}

void CreateFloorBlocks() {
        // blocks for the floor
        simplicity::Entity *floor;

        float scaling_factor = 0.05;

        // this should be done based on the shortest side, since the scaling factor is a fraction of the shorter side
        int block_width = 2 * engine.renderer_.window_dimensions_.y * scaling_factor;

        for (int i = 0; i < 8; i++) {
                // just create these on the heap for now
                resource_manager.Allocate((void*&) floor, sizeof(simplicity::Entity));
                engine.renderer_.CreateRectangle(1.0, 1.0, scaling_factor, *floor);
                floor->coords_.x = i * block_width;
                floor->type_ = simplicity::EntityType::kFloor;

                world.AddEntity(*floor);
        }
}

void SetUpEvents(simplicity::Entity &entity) {
        // function for "gravity"
        world.CreateBehavior(0, [](simplicity::Entity* entity) {
                // TODO determine "floor" by checking blocks
                if (entity->coords_.y > 0)
                        entity->coords_.y -= 3;
                });

        world.RegisterBehavior(0, &entity);
}
