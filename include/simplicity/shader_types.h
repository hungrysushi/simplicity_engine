#pragma once

namespace simplicity {

enum class ShaderError {
        kSuccess,
        kFileReadError,
        kVertexCompileError,
        kFragmentCompileError,
        kProgramLinkError,
        kShaderActiveError,
};

}  // namespace simplicity
