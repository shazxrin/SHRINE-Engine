#pragma once

#include <string>

struct Uniform {
	static constexpr std::string_view TRANSFORM = "transform";
	static constexpr std::string_view VIEW = "view";
	static constexpr std::string_view PROJECTION = "projection";
};
