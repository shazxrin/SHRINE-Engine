#include "Model.hpp"

Model::Model(uint32_t vaoId, uint32_t vboId, uint32_t eboId, uint32_t verticesCount, Material* material)
{
	this->vaoId = vaoId;
	this->vboId = vboId;
	this->eboId = eboId;

	this->verticesCount = verticesCount;

	this->material = material;
}

Model::~Model()
{
	glDeleteVertexArrays(1, &vaoId);
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &eboId);
}

uint32_t Model::GetVAOId()
{
	return this->vaoId;
}

uint32_t Model::GetVerticesCount()
{
	return this->verticesCount;
}

Material* Model::GetMaterial()
{
	return this->material;
}
