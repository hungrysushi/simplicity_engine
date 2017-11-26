
#include "simplicity/renderer.h"

#include "glad/glad.h"

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

RendererError Renderer::GenerateVertexArrays(const float* vertices, const int num_vertices, const int vertex_stride, const int vertex_offset, const unsigned int* indices, const int num_indices, Entity& entity) {
        // if indices are given, assume that they are groups of triangles

        unsigned int vertex_buffer, element_buffer, vertex_array;
        glGenBuffers(1, &vertex_buffer);
        glGenBuffers(1, &element_buffer);
        glGenVertexArrays(1, &vertex_array);

        // set the vertex array as our current context
        glBindVertexArray(vertex_array);

        // copy vertex data into the buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, num_vertices, vertices, GL_STATIC_DRAW);

        // copy the index data into element buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices, indices, GL_STATIC_DRAW);

        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_stride * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);

        // color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_stride * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_stride * sizeof(float), (void*) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // unbind the buffers and arrays
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // save our pointers into the entity
        entity.vertex_id_ = vertex_buffer;
        entity.num_points_ = num_indices;  // for an EBO, the number of points to draw is the number of indices
        entity.use_element_buffer_ = true;

        // TODO we haven't actually checked any errors
        return RendererError::kSuccess;
}

RendererError Renderer::CreateRectangle(const float x, const float y, const float scale, Entity& entity) {

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

        // generate and bind vertex object to entity
        return GenerateVertexArrays(vertices, sizeof(vertices), 8, 3, indices, sizeof(indices), entity);
}

RendererError Renderer::DrawObject() {
        // TODO
}

RendererError Renderer::DrawWorld() {
        // TODO
}

}  // namespace simplicity
