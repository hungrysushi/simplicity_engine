#pragma once

#include <vector>

#include "newton/basic_entity.h"

namespace simplicity {

class Newton {
public:
        Newton();
        ~Newton();
        SimpleDetectCollision(vector<vector<int>> a, vector<vector<int>> b)
        bool AABB(BasicEntity& a, BasicEntity& b);

private:
};

} /* namespace simplicity */
