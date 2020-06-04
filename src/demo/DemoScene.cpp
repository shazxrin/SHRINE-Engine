#include "DemoScene.hpp"
#include "model/ModelLoader.hpp"

DemoScene::DemoScene()
{
	// Setup camera.
	camera = std::make_shared<Camera>();
	camera->position = glm::vec3(0.0f, 0.0f, 3.0f);
	camera->target = glm::vec3(0.0f, 0.0f, 0.0f);
	camera->up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Load model into an entity.
	std::shared_ptr<Model> testModel(ModelLoader::LoadModelFromFile("test.obj"));
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
	float camMovementDelta = 0.01f * deltaTime;
	if (InputManager::IsKeyPressed(GLFW_KEY_W))
	{
		camera->position.y += camMovementDelta;
		camera->target.y += camMovementDelta;
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_A))
	{
		camera->position.x -= camMovementDelta;
		camera->target.x -= camMovementDelta;
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_S))
	{
		camera->position.y -= camMovementDelta;
		camera->target.y -= camMovementDelta;
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_D))
	{
		camera->position.x += camMovementDelta;
		camera->target.x += camMovementDelta;
	}

	Renderer::RenderModel(camera, entity, shaderProgram);
}
