#include "simplicity/shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>

namespace simplicity {

Shader::Shader() {

}

Shader::~Shader() {

}

ShaderError Shader::Initialize(const char* vertex_path, const char* fragment_path) {

        // read the source from file
        std::string vertex_code;
        std::string fragment_code;
        std::ifstream vertex_file;
        std::ifstream fragment_file;

        // turn on file read exceptions
        vertex_file.exceptions( std::ifstream::failbit | std::ifstream::badbit );
        fragment_file.exceptions( std::ifstream::failbit | std::ifstream::badbit );

        try {

                vertex_file.open(vertex_path);
                fragment_file.open(fragment_path);

                std::stringstream vertex_stream, fragment_stream;
                vertex_stream << vertex_file.rdbuf();
                fragment_stream << fragment_file.rdbuf();

                vertex_file.close();
                fragment_file.close();

                vertex_code = vertex_stream.str();
                fragment_code = fragment_stream.str();

        } catch (std::ifstream::failure e) {
                std::cout << "Failed to read shader files" << std::endl;
                return ShaderError::kFileReadError;
        }

        const char* vertex_code_char = vertex_code.c_str();
        const char* fragment_code_char = fragment_code.c_str();

        unsigned int vertex, fragment;
        int success;
        char log[512];

        // create the vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertex_code_char, nullptr);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
                glGetShaderInfoLog(vertex, 512, nullptr, log);
                std::cout << "Vertex compilation failed\n" << log << std::endl;
                return ShaderError::kVertexCompileError;
        }

        // create the fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragment_code_char, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
                glGetShaderInfoLog(fragment, 512, nullptr, log);
                std::cout << "Fragment compilation failed\n" << log << std::endl;
                return ShaderError::kFragmentCompileError;
        }

        // link the program
        shader_id_ = glCreateProgram();
        glAttachShader(shader_id_, vertex);
        glAttachShader(shader_id_, fragment);
        glLinkProgram(shader_id_);
        glGetProgramiv(shader_id_, GL_LINK_STATUS, &success);
        if (!success) {
                glGetProgramInfoLog(shader_id_, 512, nullptr, log);
                std::cout << "Program linking failed\n" << log << std::endl;
                return ShaderError::kProgramLinkError;
        }

        // no longer need the shaders after we've linked them into a program
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return ShaderError::kSuccess;
}

ShaderError Shader::SetActive() {
        glUseProgram(shader_id_);

        return (glGetError() == GL_NO_ERROR) ? ShaderError::kSuccess : ShaderError::kShaderActiveError;
}

}  // namespace simplicity
