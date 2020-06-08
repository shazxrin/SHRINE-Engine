#pragma once

#include <cstdint>
#include <string>

struct Attribute {
	static constexpr uint8_t POSITION_LOCATION = 0;
	static constexpr std::string_view POSITION_NAME = "position";

	static constexpr uint8_t NORMAL_LOCATION = 1;
	static constexpr std::string_view NORMAL_NAME = "normal";

	static constexpr uint8_t UV_COORDS_LOCATION = 2;
	static constexpr std::string_view UV_COORDS_NAME = "uvCoords";
};
