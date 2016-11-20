#version 150

in vec3 position;
in vec3 normal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 transformMatrix;
uniform mat4 model;

void main() {
	Normal = mat3(transpose(inverse(model))) * normal;
	FragPos = (model * vec4(position, 1.0)).xyz;
	gl_Position = transformMatrix * vec4(position, 1.0);
}