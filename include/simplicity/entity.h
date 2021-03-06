#pragma once

#include <string>

#include "simplicity/types/common_types.h"
#include "simplicity/types/entity_types.h"

namespace simplicity {

class Entity {
public:
        Entity(const std::string& label);
        Entity(const std::string& label, const EntityType type);
        ~Entity();

        void Initialize();

        std::string label_;
        EntityType type_;
        Vec3 coords_;

        // TODO Vertex and textures
        unsigned int vertex_id_;
        unsigned int num_points_;
        bool use_element_buffer_;
};

}  // namespace simplicity
