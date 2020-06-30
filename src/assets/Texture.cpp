#include "Texture.hpp"

Texture::Texture(std::string name, uint32_t id)
{
	this->name = name;
	this->id = id;
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->id);
}

std::string Texture::GetName()
{
	return this->name;
}

uint32_t Texture::GetTextureId()
{
	return this->id;
}
