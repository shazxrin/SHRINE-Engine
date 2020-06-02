#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glm/mat4x4.hpp>

#include "Shader.hpp"

class ShaderProgram
{
private:
	uint32_t shaderProgramId;
	std::vector<std::shared_ptr<Shader>> shaders;
public:
	ShaderProgram();
	~ShaderProgram();
	
	void AddShader(Shader* shader);
	void Build();

	void SetMatrix4(std::string uniformName, glm::mat4 value);

	void Start();
	void Stop();
};
