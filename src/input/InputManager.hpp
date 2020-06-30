#pragma once

#include <cstdint>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "graphics/DisplayManager.hpp"
#include "Config.hpp"

class InputManager
{
private:
	static bool IsKeyOfState(int32_t key, int32_t state);
public:
	static bool IsKeyPressed(int32_t key);
	static bool IsKeyRelease(int32_t key);
	static bool IsKeyRepeat(int32_t key);
	static glm::vec2 GetMousePos();
	static void SetMousePos(glm::vec2 pos);
};
