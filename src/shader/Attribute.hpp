#pragma once

#include <cstdint>
#include <string>

struct Attribute {
	static constexpr uint8_t POSITION_LOCATION = 0;
	static constexpr std::string_view POSITION_NAME = "position";
};
