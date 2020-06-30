#pragma once

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entities/Light.hpp"
#include "entities/Entity.hpp"
#include "entities/Camera.hpp"
#include "shader/ShaderProgram.hpp"
#include "shader/Uniform.hpp"
#include "assets/Attribute.hpp"

class Renderer 
{
public:
	static void RenderModel(std::shared_ptr<Light> light, std::shared_ptr<Camera> camera, std::shared_ptr<Entity> entity, std::shared_ptr<ShaderProgram> shaderProgram);
};