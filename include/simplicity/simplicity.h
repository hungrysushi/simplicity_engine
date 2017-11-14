#pragma once

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "simplicity/renderer.h"
#include "simplicity/simplicity_types.h"

namespace simplicity {

class Simplicity {
public:
        Simplicity();
        ~Simplicity();

        EngineError InitWindow(const int x, const int y, const std::string& label);
        void Demo();

        Renderer renderer_;
        GLFWwindow* window_ = nullptr;
};

}  /* namespace simplicity */
