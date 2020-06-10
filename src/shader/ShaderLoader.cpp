#include "ShaderLoader.hpp"

std::string ShaderLoader::LoadShaderSourceFile(std::string fileName)
{
	std::string shaderSourceStr;

	std::ifstream shaderSource;
	shaderSource.open(fileName);

	std::stringstream strStream;
	strStream << shaderSource.rdbuf();
	shaderSourceStr = strStream.str();

	shaderSource.close();

	return shaderSourceStr;
}

Shader* ShaderLoader::LoadShaderFromFile(std::string fileName, uint32_t shaderType)
{
	std::string shaderSource = LoadShaderSourceFile(fileName);
	const char* shaderSourceStr = shaderSource.c_str();
	const int shaderSourceStrLength = shaderSource.size();

	unsigned int shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderSourceStr, &shaderSourceStrLength);
	glCompileShader(shaderId);

	GLint shaderCompileStatus;
	char errorMsgBuffer[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompileStatus);
	if (shaderCompileStatus != GL_TRUE) {
		std::cout << "Failed to compile shader!" << std::endl;

		glGetShaderInfoLog(shaderId, 512, NULL, errorMsgBuffer);
		std::string errorMsg(errorMsgBuffer, 512);

		std::cout << errorMsg << std::endl;
	}

	ShaderType type;
	if (shaderType == GL_VERTEX_SHADER)
	{
		type = ShaderType::VERTEX;
	}
	else if (shaderType == GL_FRAGMENT_SHADER)
	{
		type = ShaderType::FRAGMENT;
	}

	return new Shader(shaderId, type);
}

Shader* ShaderLoader::LoadVertexShaderFromFile(std::string fileName)
{
	return LoadShaderFromFile(fileName, GL_VERTEX_SHADER);
}

Shader* ShaderLoader::LoadFragmentShaderFromFile(std::string fileName)
{
	return LoadShaderFromFile(fileName, GL_FRAGMENT_SHADER);
}
