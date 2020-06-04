#include "InputManager.hpp"

std::vector<KeyboardEventListener> InputManager::listeners = {};

void InputManager::Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (auto listener : listeners)
	{
		KeyboardEvent event;
		switch (action)
		{
		case GLFW_PRESS:
			event = KeyboardEvent::PRESSED;
			break;
		case GLFW_RELEASE:
			event = KeyboardEvent::RELEASE;
			break;
		case GLFW_REPEAT:
			event = KeyboardEvent::REPEAT;
			break;
		};
		

		listener(key, event);
	}
}

void InputManager::Setup(GLFWwindow* window)
{
	glfwSetKeyCallback(window, InputManager::Callback);
}

void InputManager::AddListener(KeyboardEventListener listener)
{
	listeners.push_back(listener);
}

void InputManager::RemoveListener(uint32_t listenerId)
{
}
