#version 450 core
uniform sampler2D text;
uniform bool has_tex;

in vec2 tex_coord;
in vec3 in_color;

out vec4 out_color;

void main()
{
    if(has_tex) {
        out_color = texture(text, tex_coord);
    } else {
        //out_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        out_color = vec4(cos(in_color)/3, 1.0f);
    }
}
