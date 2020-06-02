#pragma once

#include <vector>
#include <cstdint>

#include "Vertex.hpp"

class Mesh {
private:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
public:
	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);

	std::vector<Vertex>& GetVertices();
	std::vector<uint32_t>& GetIndices();
};