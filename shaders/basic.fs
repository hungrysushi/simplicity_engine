#version 330 core

uniform sampler2D texture1;
uniform int texture_enable;

out vec4 FragColor;

in vec3 new_color;
in vec2 tex_coords;

void main()
{
        if (texture_enable > 0) {
                FragColor = texture(texture1, tex_coords);
        } else {
                FragColor = vec4(new_color, 1.0f);
        }
}
