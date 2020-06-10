#pragma once

#include <vector>
#include <cstdint>

#include "geometry/Vertex.hpp"

class Mesh 
{
private:
	std::vector<Vertex> vertexes;
	std::vector<uint32_t> indices;
public:
	Mesh(std::vector<Vertex> vertexes, std::vector<uint32_t> indices);

	std::vector<Vertex>& GetVertexes();
	std::vector<uint32_t>& GetIndices();
};
