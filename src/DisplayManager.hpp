#pragma once

#include "Result.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class DisplayManager 
{
private:
	static GLFWwindow* window;
public:
	static Result InitWindow();
	static void InitViewport();
	static void CloseWindow();

	static GLFWwindow* GetWindow();

	static bool HasWindowInit();
	static bool ShouldWindowClose();
};