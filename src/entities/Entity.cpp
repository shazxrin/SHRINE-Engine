#include "Entity.hpp"

Entity::Entity(std::shared_ptr<Model> model)
{
	this->model = model;

	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

std::shared_ptr<Model> Entity::GetModel()
{
	return this->model;
}
