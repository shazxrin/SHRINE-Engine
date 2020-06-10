#pragma once

#include <string>

struct Uniform 
{
	static constexpr std::string_view TRANSFORM = "transform";
	static constexpr std::string_view VIEW = "view";
	static constexpr std::string_view PROJECTION = "projection";
	static constexpr std::string_view BASE_TEXTURE = "baseTexture";
	static constexpr std::string_view LIGHT_POSITION = "lightPosition";
	static constexpr std::string_view LIGHT_COLOR = "lightColor";
	static constexpr std::string_view CAMERA_POSITION = "cameraPosition";
	static constexpr std::string_view SHININESS = "shininess";
};
