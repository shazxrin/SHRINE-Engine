#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uvCoords;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoords;

void main() {
	gl_Position = projection * view * transform * vec4(position.x, position.y, position.z, 1.0f);

	texCoords = uvCoords;
}
