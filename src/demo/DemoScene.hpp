#pragma once

#include <memory>

#include "entities/Camera.hpp"
#include "entities/Entity.hpp"
#include "input/InputManager.hpp"
#include "shader/ShaderProgram.hpp"
#include "shader/ShaderLoader.hpp"
#include "Renderer.hpp"
#include "shader/Shader.hpp"
#include "scene/Scene.hpp"

class DemoScene : public Scene 
{
private:
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Entity> entity;
	std::shared_ptr<ShaderProgram> shaderProgram;
public:
	DemoScene();

	void Update(float deltaTime);
};