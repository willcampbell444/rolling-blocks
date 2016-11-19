#version 150

in vec2 position;

uniform mat4 projection;

void main() {
	vec4 pos = projection * vec4(position, 0, 1);
	gl_Position = vec4(pos.x, pos.y, pos.z, pos.w);
}