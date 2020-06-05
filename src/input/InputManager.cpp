#include "InputManager.hpp"

bool InputManager::IsKeyOfState(int32_t key, int32_t state)
{
	int32_t currentKeyState = glfwGetKey(DisplayManager::GetWindow(), key);
	if (currentKeyState == state)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputManager::IsKeyPressed(int32_t key)
{
	return InputManager::IsKeyOfState(key, GLFW_PRESS);
}

bool InputManager::IsKeyRelease(int32_t key)
{
	return InputManager::IsKeyOfState(key, GLFW_RELEASE);
}

bool InputManager::IsKeyRepeat(int32_t key)
{
	return InputManager::IsKeyOfState(key, GLFW_REPEAT);
}

glm::vec2 InputManager::GetMousePos()
{
	double x, y;
	glfwGetCursorPos(DisplayManager::GetWindow(), &x, &y);
	return glm::vec2(x, y);
}

void InputManager::SetMousePos(glm::vec2 pos)
{
	glfwSetCursorPos(DisplayManager::GetWindow(), pos.x, pos.y);
}
