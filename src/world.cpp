
#include "simplicity/world.h"

#include <iostream>

namespace simplicity {

World::World() {

}

World::~World() {

}

WorldError World::Initialize() {
        // TODO
        return WorldError::kSuccess;
}

WorldError World::AddEntity(const Entity& entity) {
        entities_.push_back(&entity);

        return WorldError::kSuccess;
}

WorldError World::PrintWorld() {
        for (auto i = entities_.begin(); i != entities_.end(); i++) {
                std::cout << (*i)->label_ << std::endl;
        }

        return WorldError::kSuccess;
}

}  // namespace simplicity
