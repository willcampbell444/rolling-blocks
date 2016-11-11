#version 330 core

in vec2 vertex;
in vec2 texCoord;

out vec2 TexCoords;

uniform mat4 projection;

void main() {
	TexCoords = texCoord;
	// gl_Position = vec4(vertex, 0, 1);
	gl_Position = projection*vec4(vertex, 0, 1);
}