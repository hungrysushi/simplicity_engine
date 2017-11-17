
#include "simplicity/entity.h"

namespace simplicity {

Entity::Entity(const std::string& label) {
        label_ = label;
        type_ = EntityType::kOther; // set up behaviors manually
}

Entity::Entity(const std::string& label, const EntityType type) {
        label_ = label;
        type_ = type;

        // based on type, we may be able to set up some default behaviors
}

Entity::~Entity() {

}

}  // namespace simplicity
