#pragma once

#include <memory>

#include <glm/vec3.hpp>

#include "assets/Scene.hpp"

class Entity 
{
private:
	std::shared_ptr<Scene> scene;
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Entity(std::shared_ptr<Scene> scene);

	std::shared_ptr<Scene> GetScene();
};
