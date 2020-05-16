#include "Model.hpp"

Model::Model(unsigned int vaoId, std::vector<unsigned int> bufferIds, unsigned int verticesCount)
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

unsigned int Model::GetVAOId()
{
	return this->vaoId;
}

unsigned int Model::GetVerticesCount()
{
	return this->verticesCount;
}
