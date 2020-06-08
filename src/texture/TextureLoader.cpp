#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "TextureLoader.hpp"

std::unordered_map<std::string, Texture*> TextureLoader::cache = {};

Texture* TextureLoader::LoadTexture(std::string fileName)
{
    auto cachedTexture = cache.find(fileName);
    if (cachedTexture != cache.end())
    {
        return cachedTexture->second;
    }

    uint32_t textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Texture wrapping parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Texture filtering parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int32_t width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // TODO: Maybe check metadata of image filetype? Didn't include Alpha channel earlier and texture messed up.
        // Very prone to bugs.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return new Texture(fileName, textureId);
}

void TextureLoader::CleanUp()
{
    for (auto cachedTexture : cache)
    {
        delete cachedTexture.second;
    }

    cache.clear();
}
