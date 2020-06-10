#pragma once

#include <cstdint>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

enum class ShaderType { VERTEX, FRAGMENT };

class Shader
{
private:
	uint32_t shaderId;
	ShaderType type;
public:
	Shader(uint32_t shaderId, ShaderType type);
	~Shader();

	uint32_t GetId();
};
