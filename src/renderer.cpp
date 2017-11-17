
#include "simplicity/renderer.h"

namespace simplicity {

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

RendererError Renderer::Initialize(Shader shader) {
        // Making an assumption here that we'll only use one type of shader.
        // May change that later
        shader_ = shader;

        return RendererError::kSuccess;
}

RendererError Renderer::CreateTriangle() {
        // TODO
}

RendererError Renderer::CreateRectangle(const float x, const float y, const float scale) {

        float x_norm, y_norm;

        // make the longer side 1.0
        if (x > y) {
                x_norm = 1.0;
                y_norm = y / x;
        } else {
                x_norm = x / y;
                y_norm = 1.0;
        }

        // scale these sides for view space
        float x_pos = x_norm * scale;
        float y_pos = y_norm * scale;

        // just map a whole texture onto the rectangle, and set the color to
        // some default.
        // TODO make the color configurable
        float vertices[] = {
                // position             // color                // texture
                x_pos, y_pos, 0.0f,     1.0f, 0.0f, 0.0f,       1.0f, 1.0f,
                x_pos, -y_pos, 0.0f,    0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
                -x_pos, y_pos, 0.0f,    0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
                -x_pos, -y_pos, 0.0f,   1.0f, 1.0f, 0.0f,       0.0f, 1.0f,
        };

        // order in which to draw the points
        unsigned int indices[] = {
                0, 1, 3,        // first triangle
                1, 2, 3,        // second triangle
        };

        // TODO return actual status
        return RendererError::kSuccess;

}

RendererError Renderer::DrawObject() {
        // TODO
}

RendererError Renderer::DrawWorld() {
        // TODO
}

}  // namespace simplicity
