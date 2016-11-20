#version 150

in vec3 Normal;
in vec3 FragPos;

out vec4 outColor;

float ambientStrength = 0.5;

vec3 lightDirection;

uniform vec3 color;
uniform vec3 cameraPosition;

void main() {
	vec3 ambient = ambientStrength * vec3(1);

	vec3 norm = normalize(Normal);
	lightDirection = normalize(vec3(1, -3, 1));
	vec3 diffuse = 0.35*max(dot(norm, -lightDirection), 0.0) * vec3(1);

	vec3 reflectDir = reflect(lightDirection, norm);
	vec3 viewDir = normalize(cameraPosition - FragPos);
	vec3 specular = 0.2*pow(max(dot(viewDir, reflectDir), 0), 256)*vec3(1);

	outColor = vec4((ambient + diffuse + specular)*color, 1);

	if (FragPos.y < -0.05) {
		outColor = mix(outColor, vec4(0.168627, 0.188235, 0.23137, 1), clamp(-(FragPos.y+0.05)/1.9, 0.0, 1.0));
	}
}