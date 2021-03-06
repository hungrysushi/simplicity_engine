#pragma once

#include <string>

#include "simplicity/types/common_types.h"
#include "simplicity/types/shader_types.h"

namespace simplicity {

class Shader {
public:
        Shader();
        ~Shader();

        ShaderError Initialize(const char* vertex_path, const char* fragment_path);
        ShaderError SetActive();
        ShaderError SetVec2(const std::string& name, const Vec2& value);
        ShaderError SetVec3(const std::string& name, const Vec3& value);

        unsigned int shader_id_;
};

}  // namespace simplicity
