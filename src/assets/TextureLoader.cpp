#include "TextureLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
        std::size_t pos = fileName.find(".");
        std::string fileExtension = fileName.substr(pos + 1);
        // TODO: Maybe check metadata of image filetype? Didn't include Alpha channel earlier and texture messed up.
        // Very prone to bugs.

        uint32_t channel = 0;
        if (fileExtension == "png")
        {
            channel = GL_RGBA;
        }
        else if (fileExtension == "jpg" || fileExtension == "jpeg")
        {
            channel = GL_RGB;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, channel, width, height, 0, channel, GL_UNSIGNED_BYTE, data);
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
