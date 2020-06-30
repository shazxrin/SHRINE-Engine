#include "DisplayManager.hpp"

GLFWwindow* DisplayManager::window = nullptr;

Result DisplayManager::InitWindow()
{
	// Create a window.
	window = glfwCreateWindow(800, 600, "SHRINE ENGINE", NULL, NULL);
	if (window == nullptr) {
		glfwTerminate();

		return Result::Fail("Failed to create a GLFW window!");
	}
	glfwMakeContextCurrent(window);

	return Result::Success();
}

void DisplayManager::InitViewport() {
	// Listen to window size changes & update viewport.
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});
}

void DisplayManager::CloseWindow()
{
	glfwDestroyWindow(window);
}

GLFWwindow* DisplayManager::GetWindow()
{
	return window;
}

bool DisplayManager::HasWindowInit()
{
	return window != nullptr;
}

bool DisplayManager::ShouldWindowClose()
{
	return glfwWindowShouldClose(window);
}
