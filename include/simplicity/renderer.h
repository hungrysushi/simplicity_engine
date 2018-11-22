#pragma once

#include "simplicity/entity.h"
#include "simplicity/shader.h"
#include "simplicity/types/renderer_types.h"
#include "simplicity/world.h"

namespace simplicity {

class Renderer {
public:
        Renderer();
        ~Renderer();

        RendererError Initialize(Shader shader);
        RendererError CreateTriangle();
        RendererError GenerateVertexArrays(const float* vertices, const int num_vertices, const int vertex_stride, const int vertex_offset, const unsigned int* indices, const int num_indices, Entity& entity);
        RendererError CreateRectangle(const float x, const float y, const float scale, Entity& entity);
        RendererError DrawObject();
        RendererError DrawWorld(const World& world);
        RendererError SetWindowDimensions(const int x, const int y);

        Shader shader_;
        Vec2 window_dimensions_;
        Vec2 window_proportions_;
};

}  // namespace simplicity
