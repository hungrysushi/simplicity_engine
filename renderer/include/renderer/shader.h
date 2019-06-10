#pragma once

#include <string>

#include "common/types.h"
#include "renderer/shader_types.h"

namespace simplicity {

class Shader {
public:
        Shader();
        ~Shader();

        ShaderError Initialize(const char* vertex_path, const char* fragment_path);
        ShaderError SetActive();
        ShaderError SetInt(const std::string& name, const int value);
        ShaderError SetVec2(const std::string& name, const Vec2& value);
        ShaderError SetVec3(const std::string& name, const Vec3& value);

        unsigned int shader_id_;
};

}  // namespace simplicity
