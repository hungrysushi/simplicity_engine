
#include "newton/basic_entity.h"

namespace simplicity {

BasicEntity::BasicEntity() {

}

BasicEntity::BasicEntity(unsigned int width, unsigned int height, unsigned int x, unsigned int y)
        : width_(width),
          height_(height),
          x_(x),
          y_(y) {

}

BasicEntity::~BasicEntity() {

}

} /* namespace simplicity */
