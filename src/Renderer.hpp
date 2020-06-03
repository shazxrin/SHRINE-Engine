#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "entities/Entity.hpp"
#include "entities/Camera.hpp"
#include "shader/ShaderProgram.hpp"

class Renderer 
{
public:
	static void RenderModel(std::shared_ptr<Camera> camera, std::shared_ptr<Entity> entity, std::shared_ptr<ShaderProgram> shaderProgram);
};