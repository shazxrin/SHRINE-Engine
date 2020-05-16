#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "ShaderProgram.hpp"

#include <iostream>

ShaderProgram::ShaderProgram()
{
	shaderProgramId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	for (auto shaderId : shaderIds)
	{
		glDetachShader(shaderProgramId, shaderId);
		glDeleteShader(shaderId);
	}

	glDeleteProgram(shaderProgramId);
}

void ShaderProgram::LoadVertexShaderFromFile(std::string fileName)
{
	const char* vertexShaderSource = LoadShaderSourceFile(fileName).c_str();

	GLint shaderCompileStatus;

	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShaderId);

	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &shaderCompileStatus);
	if (shaderCompileStatus != GL_TRUE) {
		std::cout << "Failed to compile vertex shader!" << std::endl;
	}

	shaderIds.push_back(vertexShaderId);
}

void ShaderProgram::LoadFragmentShaderFromFile(std::string fileName)
{
	const char* fragShaderSource = LoadShaderSourceFile(fileName).c_str();

	GLint shaderCompileStatus;

	unsigned int fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderId, 1, &fragShaderSource, nullptr);
	glCompileShader(fragShaderId);

	glGetShaderiv(fragShaderId, GL_COMPILE_STATUS, &shaderCompileStatus);
	if (shaderCompileStatus != GL_TRUE) {
		std::cout << "Failed to compile fragment shader!" << std::endl;
	}

	shaderIds.push_back(fragShaderId);
}

void ShaderProgram::Build()
{
	for (auto shaderId : shaderIds)
	{
		glAttachShader(shaderProgramId, shaderId);
	}
	
	glLinkProgram(shaderProgramId);
}

void ShaderProgram::Start()
{
	glUseProgram(shaderProgramId);
}

void ShaderProgram::Stop()
{
	glUseProgram(0);
}

std::string ShaderProgram::LoadShaderSourceFile(std::string fileName)
{
	std::string shaderSourceStr;

	std::ifstream shaderSource;
	shaderSource.open(fileName);

	std::stringstream strStream;
	strStream << shaderSource.rdbuf();
	shaderSourceStr = "glsl(" + strStream.str() + ")glsl";

	shaderSource.close();

	return shaderSourceStr;
}
