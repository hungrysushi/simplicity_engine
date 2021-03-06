#pragma once

#include <map>

#include "GLFW/glfw3.h"

#include "simplicity/types/input_handler_types.h"
#include "simplicity/types/global_events_types.h"

namespace simplicity {

class InputHandler {
public:
        InputHandler();
        InputHandler(GLFWwindow* window);
        ~InputHandler();

        InputHandlerError Initialize(GLFWwindow* window);
        InputHandlerError RegisterInputEvent(const Event& event, Callback callback);
        InputHandlerError ProcessInput();

        GLFWwindow* window_ = nullptr;
};

}  // namespace simplicity
