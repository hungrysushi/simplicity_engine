#pragma once

#include "simplicity/entity.h"
#include "simplicity/renderer_types.h"
#include "simplicity/shader.h"

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
        RendererError DrawWorld();

        Shader shader_;
};

}  // namespace simplicity
