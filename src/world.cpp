
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
                std::cout << "\tx:" << (*i)->coords_.x << " y:" << (*i)->coords_.y << std::endl;
        }

        return WorldError::kSuccess;
}

WorldError World::UpdateWorld() {
        // update everything that has been registered, such as gravity or timed events

        for (auto it = behavior_map_.begin(); it != behavior_map_.end(); it++) {
                // invoke the callback for each of the items in the stored vector
                Behavior behavior = it->second;

                for (auto entity = behavior.entities.begin(); entity != behavior.entities.end(); entity++) {
                        behavior.function(*entity);
                }
        }
}

WorldError World::CreateBehavior(const uint32_t& id, const std::function<void(Entity* entity)>& behavior) {

        behavior_map_[id].function = behavior;
}

WorldError World::RegisterBehavior(const uint32_t& id, Entity* entity) {

        behavior_map_[id].entities.push_back(entity);
}

}  // namespace simplicity
