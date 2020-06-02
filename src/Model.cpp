#include "Model.hpp"

Model::Model(uint32_t vaoId, std::vector<uint32_t> bufferIds, uint64_t verticesCount)
{
	this->vaoId = vaoId;
	this->bufferIds = bufferIds;
	this->verticesCount = verticesCount;
}

Model::~Model()
{
	glDeleteVertexArrays(1, &vaoId);
	glDeleteBuffers(bufferIds.size(), bufferIds.data());
}

uint32_t Model::GetVAOId()
{
	return this->vaoId;
}

uint64_t Model::GetVerticesCount()
{
	return this->verticesCount;
}
