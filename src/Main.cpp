#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "model/Model.hpp"
#include "model/ManualModelLoader.hpp"
#include "model/ModelLoader.hpp"
#include "shader/ShaderProgram.hpp"
#include "shader/ShaderLoader.hpp"
#include "DisplayManager.hpp"
#include "input/InputManager.hpp"
#include "Renderer.hpp"

std::shared_ptr<Camera> camera;

void CameraMvmtKeyboardListener(uint32_t key, KeyboardEvent event) 
{
	if (key == GLFW_KEY_W)
	{
		camera->position.y += 0.1f;
		camera->target.y += 0.1f;
	}

	if (key == GLFW_KEY_A)
	{
		camera->position.x -= 0.1f;
		camera->target.x -= 0.1f;
	}

	if (key == GLFW_KEY_S)
	{
		camera->position.y -= 0.1f;
		camera->target.y -= 0.1f;
	}

	if (key == GLFW_KEY_D)
	{
		camera->position.x += 0.1f;
		camera->target.x += 0.1f;
	}
}

int main() 
{
	// Intialize GLFW.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Initialize OpenGL window.
	Result result = DisplayManager::InitWindow();
	if (result.GetStatus() == Result::Status::FAIL)
	{
		std::cout << result.GetErrorMsg() << std::endl;

		return -1;
	}

	// Initialize GLAD.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;

		return -1;
	}

	// Set up viewport on the window.
	DisplayManager::InitViewport();

	// Set up input management.
	InputManager::Setup(DisplayManager::GetWindow());

	// Load and compile shaders.	
	Shader* vertShader = ShaderLoader::LoadVertexShaderFromFile("shaders/vertex.glsl");
	Shader* fragShader = ShaderLoader::LoadFragmentShaderFromFile("shaders/frag.glsl");
	std::shared_ptr<ShaderProgram> shaderProgram(new ShaderProgram());
	shaderProgram->AddShader(vertShader);
	shaderProgram->AddShader(fragShader);
	shaderProgram->Build();

	// Load model into an entity.
	std::shared_ptr<Model> testModel(ModelLoader::LoadModelFromFile("test.obj"));
	std::shared_ptr<Entity> entity(new Entity(testModel));
	entity->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	entity->scale = glm::vec3(1.0f, 1.0f, 1.0f);

	// Setup camera.
	camera = std::make_shared<Camera>();
	camera->position = glm::vec3(0.0f, 0.0f, 3.0f);
	camera->target = glm::vec3(0.0f, 0.0f, 0.0f);
	camera->up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Register camera movement from user input.
	InputManager::AddListener(CameraMvmtKeyboardListener);

	// Engine loop.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	while (!DisplayManager::ShouldWindowClose()) 
	{
		glClearColor(0.588f, 0.588f, 0.992f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rotate camera.
		//const float radius = 10.0f;
		//float camX = sin(glfwGetTime()) * radius;
		//float camZ = cos(glfwGetTime()) * radius;
		//camera->position.x = camX;
		//camera->position.z = camZ;

		Renderer::RenderModel(camera, entity, shaderProgram);

		glfwSwapBuffers(DisplayManager::GetWindow());
		glfwPollEvents();
	}

	DisplayManager::CloseWindow();

	glfwTerminate();

	return 0;
}
