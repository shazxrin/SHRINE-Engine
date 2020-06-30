#pragma once

#include <texture\Texture.hpp>

class Material
{
private:
	Texture* diffuse;
public:
	Material(Texture* diffuse);
	~Material();

	Texture* GetDiffuseTexture();
};
