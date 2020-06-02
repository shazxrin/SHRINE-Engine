#version 330 core

layout (location = 0) in vec3 position;

void main() {
	gl_Position = vec4(position.x * 0.5f, position.y * 0.5f, position.z * 0.5f, 1.0f);
}
