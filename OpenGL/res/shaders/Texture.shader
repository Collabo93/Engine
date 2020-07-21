#shader vertex
#version 330 core

layout(location = 0) in vec4 a_postions;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;


out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_MVP; // Modell view projection

void main() {
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	gl_Position = u_MVP * a_postions;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform vec4 u_Color;
uniform sampler2D u_Texture[32];

void main() {
	int index = int(v_TexIndex);
	if (index > 0) {
		color = texture(u_Texture[index], v_TexCoord);
	}
	else {
		color = v_Color;
	}
};