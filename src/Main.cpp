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
#include "DisplayManager.hpp"
#include "Renderer.hpp"

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

	// Test model.
	std::vector<glm::vec3> vertices {
		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f)
	};

	std::vector<unsigned int> indices {
		0, 1, 3,
		1, 2, 3
	};

	std::shared_ptr<Model> testModel(ManualModelLoader::CreateModel(vertices, indices));
	
	// Load and compile shaders.	
	std::shared_ptr<ShaderProgram> shaderProgram(new ShaderProgram());
	shaderProgram->LoadVertexShaderFromFile("shaders/vertex.glsl");
	shaderProgram->LoadFragmentShaderFromFile("shaders/frag.glsl");
	shaderProgram->Build();

	std::shared_ptr<Model> testModel2(ModelLoader::LoadModelFromFile("test.obj"));

	// Engine loop.
	while (!DisplayManager::ShouldWindowClose()) 
	{
		glClearColor(0.588f, 0.588f, 0.992f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer::RenderModel(testModel2, shaderProgram);

		glfwSwapBuffers(DisplayManager::GetWindow());
		glfwPollEvents();
	}

	DisplayManager::CloseWindow();

	glfwTerminate();

	return 0;
}
