
#include "renderer/renderer.h"
#include "renderer/images.h"

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

// give height and width in pixels, before view adjustment
RendererError Renderer::CreateRectangle(const float x, const float y, Drawable& entity) {

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
                -x_pos, -y_pos, 0.0f,   0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
                -x_pos, y_pos, 0.0f,    1.0f, 1.0f, 0.0f,       0.0f, 1.0f,
        };

        // order in which to draw the points
        unsigned int indices[] = {
                0, 1, 3,        // first triangle
                1, 2, 3,        // second triangle
        };

        // generate and bind vertex object to entity
        return GenerateVertexArrays(vertices, sizeof(vertices), 8, 3, indices, sizeof(indices), entity);
}

RendererError Renderer::CreateRectangle(const float x, const float y, const float scale, Drawable& entity) {

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

RendererError Renderer::GenerateVertexArrays(const float* vertices, const int num_vertices, const int vertex_stride, const int vertex_offset, const unsigned int* indices, const int num_indices, Drawable& entity) {
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
        entity.vertex_id_ = vertex_array;
        entity.num_points_ = num_indices;  // for an EBO, the number of points to draw is the number of indices
        entity.use_element_buffer_ = true;

        // TODO we haven't actually checked any errors
        return RendererError::kSuccess;
}

RendererError Renderer::GenerateTextures(const std::string& filename, unsigned int& texture) {

        // load data from filename
        int width, height, channels;
        char* texture_data = Images::LoadPng(filename, width, height, channels);

        if (!texture_data) {
                std::cout << "Failed to load texture " << filename << std::endl;
        }

        // determine format
        GLenum format;
        switch (channels) {
                case 1:
                        format = GL_RED;
                        break;
                case 3:
                        format = GL_RGB;
                        break;
                case 4:
                        format = GL_RGBA;
                        break;
                default:
                        break;
        }

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // set parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // load the data into the texture
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, texture_data);

        // mipmap for distances
        glGenerateMipmap(GL_TEXTURE_2D);

        // free up the buffer
        delete [] texture_data;
}

RendererError Renderer::DrawObject(const Drawable& drawable) {

        // I'm not positive this is a valid test for a texture
        if (drawable.texture_ > 0) {
                shader_.SetInt("texture_enable", drawable.texture_);
                // draw single texture
                shader_.SetInt("texture1", 0);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, drawable.texture_);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        // bind vertex buffers
        glBindVertexArray(drawable.vertex_id_);

        // render with vertex array or element buffer
        if (drawable.use_element_buffer_) {
                glDrawElements(GL_TRIANGLES, drawable.num_points_, GL_UNSIGNED_INT, 0);
        } else {
                glDrawArrays(GL_TRIANGLES, 0, drawable.num_points_);
        }

        // unbind
        glDisable(GL_BLEND);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
}

RendererError Renderer::DrawBackground(const Vec4& color) {

        // TODO allow the setting of different shaders
        shader_.SetActive();

        // set background color from the world object
        glClearColor(color.x,
                     color.y,
                     color.z,
                     color.w);
        glClear(GL_COLOR_BUFFER_BIT);
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
