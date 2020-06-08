#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.hpp"
#include "model/Attribute.hpp"

ShaderProgram::ShaderProgram()
{
	shaderProgramId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	for (auto shader : shaders)
	{
		glDetachShader(shaderProgramId, shader->GetId());
	}

	shaders.clear();

	glDeleteProgram(shaderProgramId);
}


void ShaderProgram::AddShader(Shader* shader)
{
	// TODO: How to create smart pointer using make_*().
	std::shared_ptr<Shader> sharedShader(shader);
	shaders.push_back(sharedShader);
}

void ShaderProgram::Build()
{
	for (auto shader : shaders)
	{
		glAttachShader(shaderProgramId, shader->GetId());
	}
	
	glBindAttribLocation(shaderProgramId, Attribute::POSITION_LOCATION, Attribute::POSITION_NAME.data());
	glBindAttribLocation(shaderProgramId, Attribute::NORMAL_LOCATION, Attribute::NORMAL_NAME.data());
	glBindAttribLocation(shaderProgramId, Attribute::UV_COORDS_LOCATION, Attribute::UV_COORDS_NAME.data());

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

void ShaderProgram::SetMatrix4(std::string uniformName, glm::mat4 value)
{
	// TODO: Cache uniform locations.
	uint32_t location = glGetUniformLocation(shaderProgramId, uniformName.c_str());
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}
