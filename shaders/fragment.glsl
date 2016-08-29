#version 150

uniform vec3 uniColor;

in vec3 Color;

out vec4 outColor;

void main() {
	if (uniColor == vec3(0.05, 0.05, 0.05)) {
		outColor = vec4(uniColor, 1.0);
	} else {
		outColor = vec4(Color, 1.0);
	}
}