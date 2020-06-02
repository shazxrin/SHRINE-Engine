#pragma once

#include <cstdint>
#include <string>

struct Attribute {
	static constexpr uint8_t VERTEX_POS_LOCATION = 0;
	static constexpr std::string_view VERTEX_POS_NAME = "vertex_position";
};