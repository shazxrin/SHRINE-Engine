#include <iostream>

#include "DemoWorld.hpp"

DemoWorld::DemoWorld()
{
	// Setup light.
	light = std::make_shared<Light>();
	light->position = glm::vec3(0.0f, 10.0f, 10.0f);
	light->colour = glm::vec3(1.0f, 1.0f, 1.0f);

	// Setup camera.
	camera = std::make_shared<Camera>();
	camera->position = glm::vec3(0.0f, 5.0f, 10.0f);
	camera->target = glm::vec3(0.0f, 0.0f, 0.0f);
	camera->up = glm::vec3(0.0f, 1.0f, 0.0f);
	camera->Init();

	// Load model into an entity.
	std::shared_ptr<Scene> terrain(AssetLoader::Load3DAsset("bottle.obj"));
	entity = std::make_shared<Entity>(terrain);
	entity->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	entity->scale = glm::vec3(1.0f, 1.0f, 1.0f);

	// Load and compile shaders.	
	Shader* vertShader = ShaderLoader::LoadVertexShaderFromFile("shaders/vertex.glsl");
	Shader* fragShader = ShaderLoader::LoadFragmentShaderFromFile("shaders/frag.glsl");
	shaderProgram = std::make_shared<ShaderProgram>();
	shaderProgram->AddShader(vertShader);
	shaderProgram->AddShader(fragShader);
	shaderProgram->Build();
}

void DemoWorld::Update(double deltaTime)
{
	static glm::vec2 prevMousePos = InputManager::GetMousePos();
	glm::vec2 currentMousePos = InputManager::GetMousePos();
	glm::vec2 deltaMousePos = prevMousePos - currentMousePos;
	camera->Rotate(deltaMousePos.y * 0.01f * deltaTime, deltaMousePos.x * 0.01f * deltaTime);
	prevMousePos = currentMousePos;

	float camMovementDelta = 0.005f * deltaTime;
	if (InputManager::IsKeyPressed(GLFW_KEY_E))
	{
		camera->MoveForward(camMovementDelta);
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_S))
	{
		camera->MoveLeft(camMovementDelta);
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_D))
	{
		camera->MoveBackward(camMovementDelta);
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_F))
	{
		camera->MoveRight(camMovementDelta);
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		camera->MoveDown(camMovementDelta);
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_SPACE))
	{
		camera->MoveUp(camMovementDelta);
	}

	Renderer::RenderModel(light, camera, entity, shaderProgram);
}
