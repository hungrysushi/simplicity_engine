#pragma once

#include <string>

#include "simplicity/common_types.h"
#include "simplicity/entity_types.h"

namespace simplicity {

class Entity {
public:
        Entity(const std::string& label);
        Entity(const std::string& label, const EntityType type);
        ~Entity();

        std::string label_;
        EntityType type_;
        Vec3 coords_;

        // TODO Vertex and textures
};

}  // namespace simplicity
