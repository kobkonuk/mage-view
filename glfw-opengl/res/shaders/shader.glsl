#shader #vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;

out vec4 v_color;
out vec2 v_TexCoord;

uniform mat4 projection;
uniform mat4 model;

void main() 
{
    gl_Position = projection * model * vec4(position, 1.0);
    v_color = color;
    v_TexCoord = texCoord;
};

#shader #fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform bool b_inverse;

vec4 inverse(vec4 fcolor) {
    vec4 tmpcolor = vec4(fcolor.b, fcolor.g, fcolor.r, 1);
    return tmpcolor;
}

void main()
{
    vec4 fcolor = texture(u_Texture, v_TexCoord);
    if (b_inverse == true) {
        color = inverse(fcolor);
    }
    else {
        color = fcolor;
    }
};
