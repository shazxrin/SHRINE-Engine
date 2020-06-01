#version 330 core

layout (location = 0) in vec3 position;

void main() {
	gl_Position = vec4(position.x + 0.25f, position.y  + 0.25f, position.z, 1.0f);
}
