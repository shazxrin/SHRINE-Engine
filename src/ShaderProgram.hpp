#pragma once

#include <string>
#include <vector>

class ShaderProgram
{
private:
	unsigned int shaderProgramId = -1;
	std::vector<unsigned int> shaderIds;

	std::string LoadShaderSourceFile(std::string fileName);
	void LoadShaderFromFile(std::string fileName, int shaderType);
public:
	ShaderProgram();
	~ShaderProgram();

	void LoadVertexShaderFromFile(std::string filename);
	void LoadFragmentShaderFromFile(std::string fileName);

	void Build();

	void Start();
	void Stop();
};
