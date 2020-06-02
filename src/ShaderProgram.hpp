#pragma once

#include <string>
#include <vector>

class ShaderProgram
{
private:
	uint32_t shaderProgramId = -1;
	std::vector<unsigned int> shaderIds;

	std::string LoadShaderSourceFile(std::string fileName);
	void LoadShaderFromFile(std::string fileName, uint32_t shaderType);
public:
	ShaderProgram();
	~ShaderProgram();

	void LoadVertexShaderFromFile(std::string filename);
	void LoadFragmentShaderFromFile(std::string fileName);

	void Build();

	void Start();
	void Stop();
};
