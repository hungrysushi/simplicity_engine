#pragma once

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "simplicity/input_handler.h"
#include "simplicity/renderer.h"
#include "simplicity/types/simplicity_types.h"

namespace simplicity {

void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

class Simplicity {
public:
        Simplicity();
        ~Simplicity();

        bool IsRunning();
        EngineError Initialize(const std::string& label);
        EngineError InitWindow(const int x, const int y, const std::string& label);
        EngineError CloseWindow();
        EngineError ProcessUpdate();

        Renderer renderer_;
        InputHandler input_handler_;
        GLFWwindow* window_ = nullptr;
};

}  /* namespace simplicity */
