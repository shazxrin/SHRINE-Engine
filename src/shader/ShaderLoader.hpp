#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader/Shader.hpp"

class ShaderLoader
{
private:
	static std::string LoadShaderSourceFile(std::string fileName);
	static Shader* LoadShaderFromFile(std::string fileName, uint32_t shaderType);
public:
	static Shader* LoadVertexShaderFromFile(std::string filename);
	static Shader* LoadFragmentShaderFromFile(std::string fileName);
};
