#pragma once

#include <assets\Texture.hpp>

class Material
{
private:
	Texture* diffuse;
public:
	Material(Texture* diffuse);
	~Material();

	Texture* GetDiffuseTexture();
};
