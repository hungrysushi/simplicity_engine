#pragma once

#include <string>

#include "simpicity/shader_types.h"

namespace simplicity {

class Shader {
public:
        Shader();
        ~Shader();

        ShaderError Initialize(const char* vertex_path, const char* fragment_path);
        ShaderError Use();
};

}  // namespace simplicity
