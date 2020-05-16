#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/vec3.hpp"

#include "Model.hpp"
#include "ShaderProgram.hpp"

class Renderer 
{
public:
	static void RenderModel(Model* model, ShaderProgram* shaderProgram);
};