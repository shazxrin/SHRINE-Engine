#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "DisplayManager.hpp"
#include "demo/DemoScene.hpp"
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

	// Set up demo scene.
	std::shared_ptr<DemoScene> demoScene = std::make_shared<DemoScene>();

	// Engine loop.
	float prevTime = 0.0f;
	float currentTime = 0.0f;
	float deltaTime = 0.0f;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	while (!DisplayManager::ShouldWindowClose()) 
	{
		// Calculate delta time (in millis).
		currentTime = glfwGetTime() * 1000.0f;
		deltaTime = currentTime - prevTime;
		// TODO: Implement FPS limit here (deltaTime <= 1000/60 and sleep for 60 fps).
		prevTime = currentTime;

		glfwPollEvents();

		glClearColor(0.588f, 0.588f, 0.992f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		demoScene->Update(deltaTime);

		glfwSwapBuffers(DisplayManager::GetWindow());
	}

	DisplayManager::CloseWindow();

	glfwTerminate();

	return 0;
}
