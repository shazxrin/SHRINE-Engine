#include "ManualModelLoader.hpp"
#include "shader/Attribute.hpp"

uint32_t ManualModelLoader::currentVAOId = 0;
uint32_t ManualModelLoader::currentVBOId = 0;

void ManualModelLoader::CreateAndBindVAO()
{
	glGenVertexArrays(1, &currentVAOId);
	glBindVertexArray(currentVAOId);
}

void ManualModelLoader::AddData(uint8_t attributeId, std::vector<float> dataVector)
{
	glGenBuffers(1, &currentVBOId);
	glBindBuffer(GL_ARRAY_BUFFER, currentVBOId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * dataVector.size(), dataVector.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attributeId, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

uint32_t ManualModelLoader::AddIndices(std::vector<uint32_t> indices)
{
	uint32_t eboId = -1;
	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	return eboId;
}

void ManualModelLoader::UnbindVAO()
{
	glBindVertexArray(0);
}

Model* ManualModelLoader::CreateModel(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices)
{
	CreateAndBindVAO();
	
	std::vector<float> verticesData;
	for (auto vertex : vertices) 
	{
		verticesData.push_back(vertex.x);
		verticesData.push_back(vertex.y);
		verticesData.push_back(vertex.z);
	}
	AddData(Attribute::VERTEX_POS_LOCATION, verticesData);
	unsigned int vertexBufferId = currentVBOId;
	
	unsigned int indicesBufferId = AddIndices(indices);

	Model* model = new Model(currentVAOId, { vertexBufferId, indicesBufferId }, indices.size());

	UnbindVAO();

	return model;
}


