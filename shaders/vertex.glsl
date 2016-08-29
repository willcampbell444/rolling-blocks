#version 150

in vec3 position;
in vec3 color;

out vec3 Color;

uniform mat4 transformMatrix;

void main() {
	Color = color;
	
	gl_Position = transformMatrix * vec4(position, 1.0);
}