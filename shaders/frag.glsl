#version 330 core

in vec2 texCoords;

uniform sampler2D baseTexture;

out vec4 FragColor;


void main() {
	FragColor = texture(baseTexture, texCoords);
}
