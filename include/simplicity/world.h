/*
 * This class represents the current "world" in the game.
 * Depending on usage, this could also be considered a "level"
 */
#pragma once

#include "simplicity/common_types.h"
#include "simplicity/world_types.h"

namespace simplicity {

class World {
public:
        World();
        ~World();
        WorldError Initialize();
        WorldError AddEntity();
        WorldError PrintWorld();

        Vec2 x_dimensions_;
        Vec2 y_dimensions_;
        Vec3 view_location_ = {0.0, 0.0, 0.0};
        Vec4 background_color_;

        // vector of entities

};

}  // namespace simplicity
