#pragma once

#include <string>
#include <unordered_map> 
#include <model/Texture.hpp>

class TextureLoader
{
private:
	static std::unordered_map<std::string, Texture*> cache;
public:
	static Texture* LoadTexture(std::string fileName);

	static void CleanUp();
};