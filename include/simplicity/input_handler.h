#pragma once

#include <map>

#include "GLFW/glfw3.h"

#include "simplicity/input_handler_types.h"

namespace simplicity {

class InputHandler {
public:
        InputHandler();
        InputHandler(GLFWwindow* window);
        ~InputHandler();

        InputHandlerError Initialize(GLFWwindow* window);
        InputHandlerError RegisterInputEvent(const Event& event, InputCallback callback);
        InputHandlerError ProcessInput();

        GLFWwindow* window_ = nullptr;

        std::map<Event, InputCallback> key_map_;
};

}  // namespace simplicity
