#pragma once

#include <vector>
#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture/Texture.hpp"

class Model 
{
private:
    uint32_t vaoId;
    uint32_t vboId;
    uint32_t eboId;

    uint32_t verticesCount;

    Texture* texture;
public:
    Model(uint32_t vaoId, uint32_t vboId, uint32_t eboId, uint32_t verticesCount, Texture* texture);
    ~Model();

    uint32_t GetVAOId();
    uint32_t GetVerticesCount();
    Texture* GetTexture();
};
