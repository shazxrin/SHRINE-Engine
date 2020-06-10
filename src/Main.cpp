#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <chrono>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "DisplayManager.hpp"
#include "texture/TextureLoader.hpp"
#include "Config.hpp"
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

	glfwSetInputMode(DisplayManager::GetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetInputMode(DisplayManager::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set up demo scene.
	std::shared_ptr<DemoScene> demoScene = std::make_shared<DemoScene>();

	// Engine loop.
	double prevTimeMillis = 0.0f;
	double currentTimeMillis = 0.0f;
	double deltaTimeMillis = 0.0f;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	while (!DisplayManager::ShouldWindowClose()) 
	{
		// Calculate delta time and release CPU if necessary.
		currentTimeMillis = glfwGetTime() * 1000.0;
		deltaTimeMillis = currentTimeMillis - prevTimeMillis;
		if (deltaTimeMillis < 1000.0 / Config::TARGET_FPS)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((1000 / Config::TARGET_FPS) - static_cast<long>(deltaTimeMillis)));
			continue;
		}
		prevTimeMillis = currentTimeMillis;

		glfwPollEvents();

		glClearColor(0.588f, 0.588f, 0.992f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		demoScene->Update(deltaTimeMillis);

		glfwSwapBuffers(DisplayManager::GetWindow());
	}

	TextureLoader::CleanUp();

	DisplayManager::CloseWindow();

	glfwTerminate();

	return 0;
}
