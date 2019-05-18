
#include "simplicity/renderer.h"

#include <iostream>

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
        /* entity.vertex_id_ = vertex_buffer; */
        entity.vertex_id_ = vertex_array;
        entity.num_points_ = num_indices;  // for an EBO, the number of points to draw is the number of indices
        entity.use_element_buffer_ = true;

        // TODO we haven't actually checked any errors
        return RendererError::kSuccess;
}

// give height and width in pixels, before view adjustment
RendererError Renderer::CreateRectangle(const float x, const float y, Entity& entity) {

        // scale these sides for pixels
        float x_pos = x / window_dimensions_.x;
        float y_pos = y / window_dimensions_.y;

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
                0, 1, 2,        // first triangle
                1, 3, 2,        // second triangle
        };

        // generate and bind vertex object to entity
        return GenerateVertexArrays(vertices, sizeof(vertices), 8, 3, indices, sizeof(indices), entity);
}

RendererError Renderer::CreateRectangle(const float x, const float y, const float scale, Entity& entity) {

        float x_norm = 0.0, y_norm = 0.0;

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
                x_pos * window_proportions_.x, y_pos * window_proportions_.y, 0.0f,     1.0f, 0.0f, 0.0f,       1.0f, 1.0f,
                x_pos * window_proportions_.x, -y_pos * window_proportions_.y, 0.0f,    0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
                -x_pos * window_proportions_.x, y_pos * window_proportions_.y, 0.0f,    0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
                -x_pos * window_proportions_.x, -y_pos * window_proportions_.y, 0.0f,   1.0f, 1.0f, 0.0f,       0.0f, 1.0f,
        };

        // order in which to draw the points
        unsigned int indices[] = {
                0, 1, 2,        // first triangle
                1, 3, 2,        // second triangle
        };

        // generate and bind vertex object to entity
        return GenerateVertexArrays(vertices, sizeof(vertices), 8, 3, indices, sizeof(indices), entity);
}

RendererError Renderer::DrawObject() {
        // TODO
}

RendererError Renderer::DrawWorld(const World& world) {

        // enable the shader
        // TODO allow setting of different shaders
        shader_.SetActive();

        // set background color from the world object
        glClearColor(world.background_color_.x,
                     world.background_color_.y,
                     world.background_color_.z,
                     world.background_color_.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // pass in view params
        shader_.SetVec3("view_position", world.view_location_);

        // draw all entities
        // TODO avoid excessive draw calls by filtering the entities we need to render
        // NOTE this may cause problems with threading if someone else is acting on the world as it is rendered. We may need to iterate in a different way
        for (auto it = world.entities_.begin(); it != world.entities_.end(); it ++) {

                // dereference entitity
                Entity *entity = (Entity*) *it;

                // redundant call?
                shader_.SetActive();

                // set shader uniforms for view
                shader_.SetVec3("absolute_position", entity->coords_);
                shader_.SetVec2("window", {window_dimensions_.x, window_dimensions_.y});  // this will let us calculate proportions properly 

                // TODO load texture

                // bind vertex buffers
                glBindVertexArray(entity->vertex_id_);

                // render with vertex array or element buffer
                if (entity->use_element_buffer_) {
                        glDrawElements(GL_TRIANGLES, entity->num_points_, GL_UNSIGNED_INT, 0);
                } else {
                        glDrawArrays(GL_TRIANGLES, 0, entity->num_points_);
                }

                // unbind
                glDisable(GL_BLEND);
                glBindTexture(GL_TEXTURE_2D, 0);
                glBindVertexArray(0);
        }
}

RendererError Renderer::SetWindowDimensions(const int x, const int y) {

        // we want to set the ratio based on the longest side
        if (x > y) {  // majority of cases
                window_proportions_ = {(float) y / x, 1.0 };  // scale x down
        }  else {
                window_proportions_ = {1.0, (float) x / y };
        }

        window_dimensions_ = {(float) x, (float) y};
}

}  // namespace simplicity
