#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
{
	this->vertices = vertices;
	this->indices = indices;
}

std::vector<Vertex>& Mesh::GetVertices()
{
	return this->vertices;
}

std::vector<uint32_t>& Mesh::GetIndices()
{
	return this->indices;
}
