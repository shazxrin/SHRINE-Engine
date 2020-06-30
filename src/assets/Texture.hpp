#pragma once

#include <cstdint>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
private:
	std::string name;
	uint32_t id;
public:
	Texture(std::string name, uint32_t id);
	~Texture();

	std::string GetName();
	uint32_t GetTextureId();
};
