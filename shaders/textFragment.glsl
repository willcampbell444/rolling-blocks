#version 330 core

in vec2 TexCoords;

out vec4 outColor;

uniform sampler2D character;
uniform vec4 color;

void main() {
	outColor = vec4(color.xyz, texture(character, TexCoords).r*color.a);
}