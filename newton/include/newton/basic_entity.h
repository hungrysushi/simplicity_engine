#pragma once

#include <cinttypes>

#include "simplicity/types/common_types.h"

namespace simplicity {

class BasicEntity {
public:
        BasicEntity();
        BasicEntity(unsigned int width, unsigned int height, unsigned int x, unsigned int y);
        ~BasicEntity();

        unsigned int width_ = 0;
        unsigned int height_ = 0;

        Vec3 coords_;
};

} /* namespace simplicity */
