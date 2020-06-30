#include "Entity.hpp"

Entity::Entity(std::shared_ptr<Scene> scene)
{
	this->scene = scene;

	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

std::shared_ptr<Scene> Entity::GetScene()
{
	return this->scene;
}
