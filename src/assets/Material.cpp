#include "Material.hpp"

Material::Material(Texture* diffuse)
{
	this->diffuse = diffuse;
}

Material::~Material() { }

Texture* Material::GetDiffuseTexture()
{
	return this->diffuse;
}
