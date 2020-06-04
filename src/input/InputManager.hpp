#pragma once

#include <cstdint>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "DisplayManager.hpp"

class InputManager
{
private:
	static bool IsKeyOfState(int32_t key, int32_t state);
public:
	static bool IsKeyPressed(int32_t key);
	static bool IsKeyRelease(int32_t key);
	static bool IsKeyRepeat(int32_t key);
};
