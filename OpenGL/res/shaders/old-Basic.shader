#shader vertex
#version 330 core

layout(location = 0) in vec4 postions;
layout(location = 1) in vec2 texCoordinates;

out vec2 v_TexCoordinates;

uniform mat4 u_MVP; // Modell view projection

void main() {
	gl_Position = u_MVP * postions;
	v_TexCoordinates = texCoordinates;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoordinates;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() {
	vec4 texColor = texture(u_Texture, v_TexCoordinates);
	color = texColor;
};