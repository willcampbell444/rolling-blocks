#version 150

out vec4 outColor;

uniform float amount;

void main() {
	outColor = vec4(0.168627, 0.188235, 0.23137, amount);
}