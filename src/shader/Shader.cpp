#include "Shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader(uint32_t shaderId, ShaderType type)
{
	this->shaderId = shaderId;
	this->type = type;
}

Shader::~Shader()
{
	glDeleteShader(shaderId);
}

uint32_t Shader::GetId()
{
	return shaderId;
}
