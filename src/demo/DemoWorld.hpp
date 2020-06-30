#pragma once

#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/quaternion.hpp>

#include "entities/Light.hpp"
#include "entities/Camera.hpp"
#include "entities/Entity.hpp"
#include "input/InputManager.hpp"
#include "shader/ShaderProgram.hpp"
#include "shader/ShaderLoader.hpp"
#include "shader/Shader.hpp"
#include "assets/AssetLoader.hpp"
#include "world/World.hpp"
#include "Renderer.hpp"

class DemoWorld : public World
{
private:
	std::shared_ptr<Light> light;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Entity> entity;
	std::shared_ptr<ShaderProgram> shaderProgram;
public:
	DemoWorld();

	void Update(double deltaTime);
};
