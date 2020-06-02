#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "ShaderProgram.hpp"

#include <iostream>
#include "Attribute.hpp"

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

void ShaderProgram::LoadShaderFromFile(std::string fileName, uint32_t shaderType)
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

	shaderIds.push_back(shaderId);
}

void ShaderProgram::LoadVertexShaderFromFile(std::string fileName)
{
	LoadShaderFromFile(fileName, GL_VERTEX_SHADER);
}

void ShaderProgram::LoadFragmentShaderFromFile(std::string fileName)
{
	LoadShaderFromFile(fileName, GL_FRAGMENT_SHADER);
}

void ShaderProgram::Build()
{
	for (auto shaderId : shaderIds)
	{
		glAttachShader(shaderProgramId, shaderId);
	}
	
	glBindAttribLocation(shaderProgramId, Attribute::VERTEX_POS_LOCATION, Attribute::VERTEX_POS_NAME.data());

	glLinkProgram(shaderProgramId);
	glValidateProgram(shaderProgramId);
	
	GLint shaderLinkStatus;
	char errorMsgBuffer[512];
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &shaderLinkStatus);
	if (!shaderLinkStatus) {
		glGetProgramInfoLog(shaderProgramId, 512, NULL, errorMsgBuffer);
		std::cout << "Failed to link shader program!" << errorMsgBuffer << std::endl;
	}
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
	shaderSourceStr = strStream.str();

	shaderSource.close();

	return shaderSourceStr;
}
