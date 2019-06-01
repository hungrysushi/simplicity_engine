#pragma once

#include <string>

#include "common/types.h"
#include "simplicity/types/entity_types.h"
#include "newton/basic_entity.h"

namespace simplicity {

class Entity : public BasicEntity {
public:
        Entity();
        Entity(const std::string& label);
        Entity(const std::string& label, const EntityType type);
        Entity(const std::string& label, const unsigned int width, const unsigned int height);
        ~Entity();

        void Initialize();

        std::string label_;
        EntityType type_;
        /* Vec3 coords_; */

        // TODO Vertex and textures
        unsigned int vertex_id_;
        unsigned int num_points_;
        bool use_element_buffer_;
};

}  // namespace simplicity
