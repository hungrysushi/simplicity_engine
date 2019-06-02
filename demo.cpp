/*
 * This serves as a functional demo of the features and is an example
 * workflow. As more features are added, they should also be added to
 * the demo in some way.
 */

#define SHADER_DIR "../shaders/"

#include <iostream>
#include <string>

#include "simplicity/simplicity.h"
#include "simplicity/entity.h"
#include "simplicity/resource_manager.h"
#include "renderer/shader.h"
#include "common/types.h"
#include "simplicity/types/entity_types.h"
#include "renderer/renderer_types.h"
#include "simplicity/types/world_types.h"
#include "simplicity/world.h"
#include "newton/newton.h"

void DrawWorld();
void CreateFloorBlocks();
void SetUpEvents(simplicity::Entity& entity);

simplicity::Simplicity engine;
simplicity::World world;
simplicity::ResourceManager resource_manager;
uint64_t frames = 0;
simplicity::Newton newton;

simplicity::Entity floor_blocks[10];

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
        simplicity::Entity entity("demo entity", 25, 50);
        simplicity::RendererError renderer_err = engine.renderer_.CreateRectangle(25, 50, entity);
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

                // TODO this flow can certainly be improved
                // keep the player's old position
                simplicity::Vec3 old_coords = entity.coords_;

                engine.ProcessUpdate();
                std::cout << "Frame: " << frames++ << ", Elapsed time: " << engine.frame_elapsed_ns_.count() << std::endl;

                // render the world
                DrawWorld();

                // process input
                engine.input_handler_.ProcessInput();

                // update the world from the registered behaviors
                world.UpdateWorld();

                // verify the updated block for collisions
                for (auto it = world.entities_.begin(); it != world.entities_.end(); it++) {
                        // no point testing collision with ourselves
                        if (entity.vertex_id_ == (*it)->vertex_id_) {
                                continue;
                        }

                        const simplicity::Entity& block = **it;
                        if (newton.AABB(entity, block)) {
                                // todo resolve collision
                                entity.coords_ = old_coords;
                                /* ResolveCollision(); */
                        }
                }
        }

        return 0;
}

void DrawWorld() {
        // Draw the background. Just sets a simple color for now
        // TODO extend this to render more complex backgrounds, textures, etc
        engine.renderer_.DrawBackground(world.background_color_);

        // set the uniform for view location
        engine.renderer_.shader_.SetVec3("view_position", world.view_location_);

        for (auto it = world.entities_.begin(); it != world.entities_.end(); it++) {
                // dereference entity
                simplicity::Entity& entity = (simplicity::Entity&) **it;

                // set shader uniforms for transforming this object
                engine.renderer_.shader_.SetVec3("absolute_position", entity.coords_);
                engine.renderer_.shader_.SetVec2("window", {engine.renderer_.window_dimensions_.x, engine.renderer_.window_dimensions_.y});

                engine.renderer_.DrawObject(entity);
        }

}

void CreateFloorBlocks() {
        // blocks for the floor
        simplicity::Entity *floor;

        // this should be done based on the shortest side, since the scaling factor is a fraction of the shorter side
        int block_width = 50;

        for (int i = 0; i < 10; i++) {
                // this is kind of wasteful, since these are all the same kind of block
                // we should just reuse one array object
                engine.renderer_.CreateRectangle(block_width, block_width, floor_blocks[i]);
                floor_blocks[i].coords_.x = i * block_width;
                floor_blocks[i].type_ = simplicity::EntityType::kFloor;
                floor_blocks[i].width_ = block_width;
                floor_blocks[i].height_ = block_width;

                world.AddEntity(floor_blocks[i]);
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
