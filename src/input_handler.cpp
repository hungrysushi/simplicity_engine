
#include "simplicity/input_handler.h"

#include <iostream>

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

InputHandlerError InputHandler::ProcessInput() {

        // set the context to the window, just in case this is being called
        // outside of the engine update loop
        glfwMakeContextCurrent(window_);        

        // handle various input keys

        if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                std::cout << "Escape key pressed. Exiting now." << std::endl;
                glfwSetWindowShouldClose(window_, true);
        }

        if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
                std::cout << "W pressed." << std::endl;
        }

        if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
                std::cout << "A pressed." << std::endl;
        }

        if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
                std::cout << "S pressed." << std::endl;
        }

        if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
                std::cout << "D pressed." << std::endl;
        }

        // maybe this should happen before processing input...
        glfwSwapBuffers(window_);
        glfwPollEvents();

        return InputHandlerError::kSuccess;
}

}  // namespace simplicity
