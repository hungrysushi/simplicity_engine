
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

RendererError Renderer::CreateRectangle() {
        // TODO
}

RendererError Renderer::DrawObject() {
        // TODO
}

RendererError Renderer::DrawWorld() {
        // TODO
}

}  // namespace simplicity
