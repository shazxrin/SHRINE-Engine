#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uvCoords;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition;

out vec2 texCoords;
out vec3 toLightDir;
out vec3 surfaceNormal;

void main() {
	vec3 newPosition = vec3(transform * vec4(position, 1.0f));
	gl_Position = projection * view * vec4(newPosition, 1.0f);

	texCoords = uvCoords;
	toLightDir = normalize(lightPosition - newPosition);
	surfaceNormal = normalize(vec3(transform * vec4(normal, 1.0f)));
}
