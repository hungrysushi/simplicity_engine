#pragma once

#include "renderer/drawable.h"

#include "renderer/shader.h"
#include "renderer/renderer_types.h"

namespace simplicity {

class Renderer {
public:
        Renderer();
        ~Renderer();

        RendererError Initialize(Shader shader);
        RendererError CreateTriangle();
        RendererError GenerateVertexArrays(const float* vertices, const int num_vertices, const int vertex_stride, const int vertex_offset, const unsigned int* indices, const int num_indices, Drawable& entity);
        RendererError CreateRectangle(const float x, const float y, Drawable& entity);
        RendererError CreateRectangle(const float x, const float y, const float scale, Drawable& entity);
        RendererError DrawObject(const Drawable& drawable);
        RendererError DrawBackground(const Vec4& color);
        RendererError SetWindowDimensions(const int x, const int y);

        Shader shader_;
        Vec2 window_dimensions_;
        Vec2 window_proportions_;
};

}  // namespace simplicity
