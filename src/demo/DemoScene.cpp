#include <iostream>

#include "DemoScene.hpp"
#include "geometry/ModelLoader.hpp"

DemoScene::DemoScene()
{
	// Setup camera.
	camera = std::make_shared<Camera>();
	camera->position = glm::vec3(0.0f, 0.0f, 3.0f);
	camera->target = glm::vec3(0.0f, 0.0f, 0.0f);
	camera->up = glm::vec3(0.0f, 1.0f, 0.0f);
	camera->Update();

	// Load model into an entity.
	std::shared_ptr<Model> testModel(ModelLoader::LoadModelFromFile("bottle.obj"));
	entity = std::make_shared<Entity>(testModel);
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

void DemoScene::Update(float deltaTime)
{
	camera->Update();

	static glm::vec2 prevMousePos = InputManager::GetMousePos();
	glm::vec2 currentMousePos = InputManager::GetMousePos();
	glm::vec2 deltaMousePos = prevMousePos - currentMousePos;
	camera->Rotate(deltaMousePos.y, deltaMousePos.x);
	prevMousePos = currentMousePos;

	camera->Update();

	float camMovementDelta = 0.01f * deltaTime;
	if (InputManager::IsKeyPressed(GLFW_KEY_W))
	{
		camera->MoveForward(camMovementDelta);
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_A))
	{
		camera->MoveLeft(camMovementDelta);
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_S))
	{
		camera->MoveBackward(camMovementDelta);
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_D))
	{
		camera->MoveRight(camMovementDelta);
	}

	Renderer::RenderModel(camera, entity, shaderProgram);
}
