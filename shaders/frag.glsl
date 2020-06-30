#version 330 core

in vec2 texCoords;
in vec3 toCameraDir;
in vec3 toLightDir;
in vec3 surfaceNormal;

uniform vec3 lightColor;
uniform float shininess;
uniform sampler2D diffuseTexture;

out vec4 FragColor;

void main() {
	float diffuseFactor = clamp(dot(surfaceNormal, toLightDir), 0.2f, 1.0f);
	vec3 diffuseLighting = diffuseFactor * lightColor;
	
	vec3 fromLightDir = -toLightDir;
	vec3 reflectedLightDir = reflect(fromLightDir, surfaceNormal);
	float specularFactor = clamp(dot(reflectedLightDir, toCameraDir), 0.0f, 1.0f);
	specularFactor = pow(specularFactor, shininess);
	vec3 specularLighting = specularFactor * lightColor;

	//FragColor = vec4(diffuseLighting, 1.0f) * texture(baseTexture, texCoords) + vec4(specularLighting, 1.0f);
	// TODO: Models with no texture not supported. Remove line below once supported.
	FragColor = vec4(diffuseLighting, 1.0f) * texture(diffuseTexture, texCoords) + vec4(specularLighting, 1.0f);
}
