#pragma once

#include "simplicity/renderer_types.h"
#include "simplicity/shader.h"

namespace simplicity {

class Renderer {
public:
        Renderer();
        ~Renderer();

        RendererError Initialize(Shader shader);
        RendererError CreateTriangle();
        RendererError CreateRectangle(const float x, const float y, const float scale);
        RendererError DrawObject();
        RendererError DrawWorld();

        Shader shader_;
};

}  // namespace simplicity
