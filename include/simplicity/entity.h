#pragma once

#include <string>

#include "renderer/drawable.h"
#include "newton/basic_entity.h"

#include "common/types.h"
#include "simplicity/types/entity_types.h"

namespace simplicity {

class Entity : public Drawable, public BasicEntity {
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
};

}  // namespace simplicity
