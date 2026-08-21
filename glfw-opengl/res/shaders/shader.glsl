#shader #vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;

out vec4 v_color;
out vec2 v_TexCoord;

void main() 
{
	gl_Position = vec3(position, 1.0);
    v_color = color;
	v_TexCoord = texCoord;
};

#shader #fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    v_color = texture(u_Texture, v_TexCoord);
};
