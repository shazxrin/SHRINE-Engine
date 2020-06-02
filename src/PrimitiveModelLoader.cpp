#include "PrimitiveModelLoader.hpp"
#include "Attribute.hpp"

uint32_t PrimitiveModelLoader::currentVAOId = 0;
uint32_t PrimitiveModelLoader::currentVBOId = 0;

void PrimitiveModelLoader::CreateAndBindVAO()
{
	glGenVertexArrays(1, &currentVAOId);
	glBindVertexArray(currentVAOId);
}

void PrimitiveModelLoader::AddData(uint8_t attributeId, std::vector<float> dataVector)
{
	glGenBuffers(1, &currentVBOId);
	glBindBuffer(GL_ARRAY_BUFFER, currentVBOId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * dataVector.size(), dataVector.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attributeId, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

uint32_t PrimitiveModelLoader::AddIndices(std::vector<uint32_t> indices)
{
	uint32_t eboId = -1;
	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	return eboId;
}

void PrimitiveModelLoader::UnbindVAO()
{
	glBindVertexArray(0);
}

Model* PrimitiveModelLoader::CreateModel(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices)
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


