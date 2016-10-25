#version 150

in vec3 Normal;
in vec3 FragPos;

out vec4 outColor;

float ambientStrength = 0.5;

vec3 lightDirection;

uniform vec3 color;
uniform vec3 cameraPosition;
uniform bool useLighting;

void main() {
	if (useLighting) {
		vec3 ambient = ambientStrength * vec3(1);

		vec3 norm = normalize(Normal);
		lightDirection = normalize(vec3(1, -3, 1));
		vec3 diffuse = 0.35*max(dot(norm, -lightDirection), 0.0) * vec3(1);

		vec3 reflectDir = reflect(lightDirection, norm);
		vec3 viewDir = normalize(cameraPosition);
		vec3 specular = 0.5*pow(max(dot(viewDir, reflectDir), 0), 256)*vec3(1);

		outColor = vec4((ambient + diffuse + specular)*color, 1);
	} else {
		outColor = vec4(color, 1.0);
	}
}