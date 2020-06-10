#pragma once

#include <string>
#include <unordered_map> 
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture/Texture.hpp"

class TextureLoader
{
private:
	static std::unordered_map<std::string, Texture*> cache;
public:
	static Texture* LoadTexture(std::string fileName);

	static void CleanUp();
};