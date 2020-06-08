#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertexes, std::vector<uint32_t> indices)
{
	this->vertexes = vertexes;
	this->indices = indices;
}

std::vector<Vertex>& Mesh::GetVertexes()
{
	return this->vertexes;
}

std::vector<uint32_t>& Mesh::GetIndices()
{
	return this->indices;
}
