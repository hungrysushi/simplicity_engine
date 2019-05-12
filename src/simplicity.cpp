
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

bool Simplicity::IsRunning() {
        // will need more complex logic later, maybe a member bool
        // set by other functions
        return !glfwWindowShouldClose(window_);
}

EngineError Simplicity::Initialize(const std::string& label) {

        glfwInit();

        // get the window resolution
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        InitWindow(mode->width, mode->height, label);

        // set up the default input handler
        input_handler_.Initialize(window_);

        // set up a default shader
        Shader shader;
        shader.Initialize("../shaders/basic.vs", "../shaders/basic.fs");

        // TODO initialize this without shader, set shader later
        renderer_.Initialize(shader);
        renderer_.SetWindowDimensions(mode->width, mode->height);

        // start the timer
        start_time_ = std::chrono::system_clock::now();
        prev_time_ = start_time_;

        // TODO actually check errors
        return EngineError::kSuccess;
}

EngineError Simplicity::InitWindow(const int x, const int y, const std::string& label) {

        // set opengl version, and use core opengl for greater compatibility
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // create the window and save a handle
        window_ = glfwCreateWindow(x, y, label.c_str(), glfwGetPrimaryMonitor(), NULL);

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

EngineError Simplicity::CloseWindow() {
        glfwSetWindowShouldClose(window_, true);

        return (glGetError() == GL_NO_ERROR) ? EngineError::kSuccess : EngineError::kWindowCloseError;
}

EngineError Simplicity::ProcessUpdate() {
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

        frame_elapsed_ns_ = now - prev_time_;

        glfwMakeContextCurrent(window_);

        prev_time_ = now;
}

}  /* namespace simplicity */
