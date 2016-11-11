#version 330 core

in vec2 TexCoords;

out vec4 outColor;

uniform sampler2D character;

void main() {
	outColor = vec4(0.752941, 0.772549, 0.8078431, texture(character, TexCoords).r);
}