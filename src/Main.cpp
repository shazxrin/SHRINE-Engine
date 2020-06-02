#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "DisplayManager.hpp"
#include "Model.hpp"
#include "PrimitiveModelLoader.hpp"
#include "Renderer.hpp"
#include "ShaderProgram.hpp"

int main() 
{
	// Intialize GLFW.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

	std::shared_ptr<Model> testModel(PrimitiveModelLoader::CreateModel(vertices, indices));
	
	// Load and compile shaders.	
	std::shared_ptr<ShaderProgram> shaderProgram(new ShaderProgram());
	shaderProgram->LoadVertexShaderFromFile("shaders/vertex.glsl");
	shaderProgram->LoadFragmentShaderFromFile("shaders/frag.glsl");
	shaderProgram->Build();

	// Engine loop.
	while (!DisplayManager::ShouldWindowClose()) 
	{
		glClearColor(0.588f, 0.588f, 0.992f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer::RenderModel(testModel, shaderProgram);

		glfwSwapBuffers(DisplayManager::GetWindow());
		glfwPollEvents();
	}

	DisplayManager::CloseWindow();

	glfwTerminate();

	return 0;
}
