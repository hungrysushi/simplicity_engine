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

        if (a.x_ < b.x_ + b.width_ &&
            a.x_ + a.width_ > b.x_ &&
            a.y_ < b.y_ + b.height_ &&
            a.y_ + a.height_ > b.y_) {
                return true;
        }

        return false;
}

} /* namespace simplicity */
