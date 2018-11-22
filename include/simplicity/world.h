/*
 * This class represents the current "world" in the game.
 * Depending on usage, this could also be considered a "level"
 */
#pragma once

#include <map>
#include <vector>

#include "simplicity/entity.h"
#include "simplicity/types/common_types.h"
#include "simplicity/types/world_types.h"

namespace simplicity {

class World {
public:
        World();
        ~World();
        WorldError Initialize();
        WorldError AddEntity(const Entity& entity);
        WorldError PrintWorld();
        WorldError UpdateWorld();
        WorldError CreateBehavior(const uint32_t& id, const std::function<void(Entity* entity)>& behavior);
        WorldError RegisterBehavior(const uint32_t& id, Entity* entity);

        Vec2 x_dimensions_;
        Vec2 y_dimensions_;

        // There may be value in putting this in a camera class later
        Vec3 view_location_ = {0.0, 0.0, 0.0};
        Vec2 view_window_ = {0.0, 0.0};

        Vec4 background_color_;

        // vector of entities
        std::vector<const Entity*> entities_;
        std::map<uint32_t, Behavior> behavior_map_;
};

}  // namespace simplicity
