#include "newton/newton.h"

namespace simplicity {

Newton::Newton() {
        // nothing to do yet
}

Newton::~Newton() {
        // nothing to do yet
}

/* Newton::SimpleDetectCollision(vector<vector<int>> a, vector<vector<int>> b) { */
    
/* } */

// basic Axis Aligned Bounding Box collision detection
// Takes two BasicEntities and returns true for a detected collision
bool Newton::AABB(const BasicEntity& a, const BasicEntity& b) {

        if (a.coords_.x < b.coords_.x + b.width_ &&
            a.coords_.x + a.width_ > b.coords_.x &&
            a.coords_.y < b.coords_.y + b.height_ &&
            a.coords_.y + a.height_ > b.coords_.y) {
                return true;
        }

        return false;
}

} /* namespace simplicity */
