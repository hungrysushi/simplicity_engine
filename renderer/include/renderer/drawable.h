#pragma once

namespace simplicity {

class Drawable {
public:
        Drawable() {};
        virtual ~Drawable() {};

        // vertex and texture info
        unsigned int vertex_id_ = 0;
        unsigned int num_points_ = 0;
        bool use_element_buffer_ = false;

        unsigned int texture_ = 0;
};

} /* namespace simplicity */
