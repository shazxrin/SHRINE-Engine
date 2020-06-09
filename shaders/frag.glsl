#version 330 core

in vec2 texCoords;
in vec3 toLightDir;
in vec3 surfaceNormal;

uniform vec3 lightColor;
uniform sampler2D baseTexture;

out vec4 FragColor;


void main() {
	float brightness = clamp(dot(surfaceNormal, toLightDir), 0.2f, 1.0f);
	vec3 diffuseLighting = brightness * lightColor;

	FragColor = vec4(diffuseLighting, 1.0f) * texture(baseTexture, texCoords);
}
