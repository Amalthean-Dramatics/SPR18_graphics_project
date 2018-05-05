#version 450 core
layout (location = 0) in vec3 pos_vec;
layout (location = 1) in vec2 uv_coord;

uniform mat4 view_matrix;

out vec2 tex_coord;

void main()
{
   gl_Position = view_matrix * vec4(pos_vec, 1.0);
   tex_coord = uv_coord;
}
