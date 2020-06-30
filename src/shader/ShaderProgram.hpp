#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "assets/Attribute.hpp"
#include "shader/Shader.hpp"

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
	void SetVec3(std::string uniformName, glm::vec3 value);
	void SetFloat(std::string uniformName, float value);

	void Start();
	void Stop();
};
