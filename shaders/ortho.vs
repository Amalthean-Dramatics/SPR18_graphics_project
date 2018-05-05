#version 450 core
layout (location = 0) in vec3 pos_vec;
layout (location = 1) in vec2 uv_coord;

uniform mat4 view_matrix;

out vec2 tex_coord;
out vec3 in_color;

void main()
{
   gl_Position = view_matrix * vec4(pos_vec, 1.0);
   in_color = vec3(pos_vec + vec3(0.25, 0.25, 0.25));
   tex_coord = uv_coord;
}
