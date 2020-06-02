#pragma once

#include <cstdint>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "Model.hpp"

class ManualModelLoader
{
private:
	static uint32_t currentVAOId;
	static uint32_t currentVBOId;

	static void CreateAndBindVAO();
	static void AddData(uint8_t attributeId, std::vector<float> data);
	static uint32_t AddIndices(std::vector<uint32_t> indices);
	static void UnbindVAO();
public:
	static Model* CreateModel(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices);
};