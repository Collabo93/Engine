#shader vertex
#version 330 core

layout(location = 0) in vec4 a_postions;
layout(location = 1) in vec4 a_Color;

out vec4 v_Color;

uniform mat4 u_MVP; // Modell view projection

void main() {
	v_Color = a_Color;
	gl_Position = u_MVP * a_postions;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;

uniform vec4 u_Color;

void main() {
	color = v_Color;
};