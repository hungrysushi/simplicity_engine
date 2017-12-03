#pragma once

#include "GLFW/glfw3.h"

#include "simplicity/input_handler_types.h"

namespace simplicity {

class InputHandler {
public:
        InputHandler();
        InputHandler(GLFWwindow* window);
        ~InputHandler();

        InputHandlerError Initialize(GLFWwindow* window);
        InputHandlerError ProcessInput();

        GLFWwindow* window_ = nullptr;
};

}  // namespace simplicity
