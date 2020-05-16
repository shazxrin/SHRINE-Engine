#pragma once

#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Model 
{
private:
    unsigned int vaoId;
    std::vector<unsigned int> bufferIds;
    unsigned int verticesCount;
public:
    Model(unsigned int vaoId, std::vector<unsigned int> bufferIds, unsigned int verticesCount);
    ~Model();

    unsigned int GetVAOId();
    unsigned int GetVerticesCount();
};

