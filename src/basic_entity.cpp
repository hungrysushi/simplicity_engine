
#include "newton/basic_entity.h"
#include "simplicity/types/common_types.h"

namespace simplicity {

BasicEntity::BasicEntity() {

}

BasicEntity::BasicEntity(unsigned int width, unsigned int height)
        : width_(width),
          height_(height) {

}

BasicEntity::~BasicEntity() {

}

} /* namespace simplicity */
