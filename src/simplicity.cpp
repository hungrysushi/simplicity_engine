
#include "simplicity/simplicity.h"

#include <iostream>

#include "simplicity/shader.h"

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

        Shader shader;
        shader.Initialize("../shaders/basic.vs", "../shaders/basic.fs");

        renderer_.Initialize(shader);
}

}  /* namespace simplicity */
