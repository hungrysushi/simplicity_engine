
#include "simplicity/simplicity.h"

#include <iostream>

#include "simplicity/shader.h"
#include "simplicity/world.h"

namespace simplicity
{

Simplicity::Simplicity() {

}

Simplicity::~Simplicity() {

}

EngineError Simplicity::InitWindow(const int x, const int y, const std::string& label) {

        glfwInit();

        // set opengl version, and use core opengl for greater compatibility
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // create the window and save a handle
        window_ = glfwCreateWindow(x, y, label.c_str(), NULL, NULL);

        if (window_ == NULL) {
                std::cout << "Failed to open window" << std::endl;
                glfwTerminate();
                return EngineError::kWindowCreateError;
        }

        glfwMakeContextCurrent(window_);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                std::cout << "Could not initialize GLAD" << std::endl;
                glfwTerminate();
                return EngineError::kGladError;
        }

        // successfully created the window
        return EngineError::kSuccess;
}

/*
 * This serves as a functional demo of the features and is an example
 * workflow. As more features are added, they should also be added to
 * the demo in some way.
 */
void Simplicity::Demo() {
        // TODO

        InitWindow(100, 100, "Demo");

        Shader shader;
        shader.Initialize("../shaders/basic.vs", "../shaders/basic.fs");

        renderer_.Initialize(shader);

        // create the world
        World world;

        // create entities in shared pointers
        // ex. RendererError renderer_err = renderer_.CreateRectangle(&entity);
        Entity entity("demo entity");
        RendererError renderer_err = renderer_.CreateRectangle(5.0, 5.0, 0.5, entity);

        // add entities to the world
        // ex. WorldError world_err = world_.AddEntity(entity);
        WorldError world_err = world.AddEntity(entity);

        // Debug
        world.PrintWorld();

        while (true) {
                // update the world
                // note: in order to update any of the entity characteristics,
                // we will have to hold on to the objects.
                // The other way to give entities behaviors is by callbacks

                // render the world

                // process input
        }
}

}  /* namespace simplicity */
