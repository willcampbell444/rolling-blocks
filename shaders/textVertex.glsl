#version 330 core

in vec3 vertex;
in vec2 texCoord;

out vec2 TexCoords;

uniform mat4 projection;

void main() {
	TexCoords = texCoord;
	gl_Position = projection*vec4(vertex, 1.0);
}