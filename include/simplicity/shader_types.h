#pragma once

namespace simplicity {

enum ShaderError {
        kSuccess,
        kFileReadError,
        kVertexCompileError,
        kFragmentCompileError,
        kProgramLinkError,
        kShaderActiveError,
};

}  // namespace simplicity
