#pragma once

#include <vector>
#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Material.hpp"

class Model 
{
private:
    uint32_t vaoId;
    uint32_t vboId;
    uint32_t eboId;

    uint32_t verticesCount;

    Material* material;
public:
    Model(uint32_t vaoId, uint32_t vboId, uint32_t eboId, uint32_t verticesCount, Material* material);
    ~Model();

    uint32_t GetVAOId();
    uint32_t GetVerticesCount();
    Material* GetMaterial();
};
