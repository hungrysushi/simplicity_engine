#pragma once

#include <string>

#include "simplicity/shader_types.h"

namespace simplicity {

class Shader {
public:
        Shader();
        ~Shader();

        ShaderError Initialize(const char* vertex_path, const char* fragment_path);
        ShaderError SetActive();

        unsigned int shader_id_;
};

}  // namespace simplicity
