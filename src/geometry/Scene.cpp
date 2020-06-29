#include "Scene.hpp"

Scene::Scene(std::vector<Model*> models)
{
	this->models = models;
}

Scene::~Scene()
{
	for (Model* model : models)
	{
		delete model;
	}
}

std::vector<Model*> Scene::GetModels()
{
	return models;
}
