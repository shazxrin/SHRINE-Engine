#pragma once

#include <cstdint>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum class KeyboardEvent { PRESSED, RELEASE, REPEAT };

typedef void (*KeyboardEventListener)(uint32_t key, KeyboardEvent event);

class InputManager
{
private:
	static std::vector<KeyboardEventListener> listeners;
	static void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
public:
	static void Setup(GLFWwindow* window);
	static void AddListener(KeyboardEventListener listener);
	static void RemoveListener(uint32_t listenerId);
};