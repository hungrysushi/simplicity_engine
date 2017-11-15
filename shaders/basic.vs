#version 330 core

layout (location = 0) in vec3 position_coords;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texture_coords;

// these coordinates are in the world space
uniform vec3 view_position;  // position of the camera
uniform vec3 absolute_position;  // position of the object
uniform vec2 window;  // dimensions of the view window

// time that window has been open
uniform float get_time;

// outputs to the fragment shader
out vec3 new_color;
out vec2 tex_coords;

void main()
{
        // adjust the world coordinates to the normalized gl coordinates
        vec3 relative_view = absolute_position - view_position;
        vec3 normal_view = vec3(relative_view.x / window.x,
                                relative_view.y / window.y,
                                0.0);  // this is a 2D system, don't need this

        // shift the shape coordinates to the normalized position
        vec3 normal_position = pos + normal_view;
        gl_Position = vec4(normal_position, 1.0f);

        // this is just for fun. Change the color with respect to time and position
        new_color = color + vec3(sin(view_position.x/window.x),
                                 sin(view_position.y/window.y),
                                 sin(get_time));

        // pass the texture coordinates to the fragment shader
        tex_coords = texture_coords;
}
