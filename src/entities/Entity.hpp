#pragma once

#include <memory>

#include <glm/vec3.hpp>

#include "geometry/Model.hpp"

class Entity {
private:
	std::shared_ptr<Model> model;
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Entity(std::shared_ptr<Model> model);

	std::shared_ptr<Model> GetModel();
};