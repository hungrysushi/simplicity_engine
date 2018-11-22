#pragma once

#include <functional>
#include <vector>

namespace simplicity {

enum class WorldError {
        kSuccess,
};

// TODO all of this should be sent through the global events handler somehow
struct Behavior {
        std::function<void(Entity* entity)> function;
        std::vector<Entity*> entities;
};

}  // namespace simplicity
