#pragma once

#include <cstdint>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/vec3.hpp"
#include "Model.hpp"

class PrimitiveModelLoader
{
private:
	static unsigned int currentVAOId;
	static unsigned int currentVBOId;

	static void CreateAndBindVAO();
	static void AddData(unsigned int attributeId, std::vector<float> data);
	static unsigned int AddIndices(std::vector<unsigned int> indices);
	static void UnbindVAO();
public:
	static Model* CreateModel(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
};