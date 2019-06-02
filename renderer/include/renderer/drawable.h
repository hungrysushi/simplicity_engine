#pragma once

namespace simplicity {

class Drawable {
public:
        Drawable() {};
        virtual ~Drawable() {};

        // TODO vertex and textures
        unsigned int vertex_id_;
        unsigned int num_points_;
        bool use_element_buffer_;
};

} /* namespace simplicity */
