
#include "simplicity/input_handler.h"

#include <iostream>

#include "simplicity/global_events.h"

namespace simplicity {

InputHandler::InputHandler() {

}

InputHandler::InputHandler(GLFWwindow* window) {

        window_ = window;
}

InputHandler::~InputHandler() {

}

InputHandlerError InputHandler::Initialize(GLFWwindow* window) {
        window_ = window;
}

InputHandlerError InputHandler::RegisterInputEvent(const Event& event, const Callback callback) {
        RegisterEvent(event, callback);
}

InputHandlerError InputHandler::ProcessInput() {

        // set the context to the window, just in case this is being called
        // outside of the engine update loop
        glfwMakeContextCurrent(window_);        

        // handle various input keys

        if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                ProcessEvent(Event::kEscKeyPress);
        }

        if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
                ProcessEvent(Event::kWKeyPress);
        }

        if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
                ProcessEvent(Event::kAKeyPress);
        }

        if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
                ProcessEvent(Event::kSKeyPress);
        }

        if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
                ProcessEvent(Event::kDKeyPress);
        }

        // maybe this should happen before processing input...
        glfwSwapBuffers(window_);
        glfwPollEvents();

        return InputHandlerError::kSuccess;
}

}  // namespace simplicity
