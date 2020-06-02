#pragma once

#include <vector>
#include <cstdint>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Model 
{
private:
    uint32_t vaoId;
    std::vector<uint32_t> bufferIds;
    uint64_t verticesCount;
public:
    Model(uint32_t vaoId, std::vector<uint32_t> bufferIds, uint64_t verticesCount);
    ~Model();

    uint32_t GetVAOId();
    uint64_t GetVerticesCount();
};

