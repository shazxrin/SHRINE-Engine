#pragma once

#include <vector>
#include "Model.hpp"

class Scene
{
private:
	std::vector<Model*> models;
public:
	Scene(std::vector<Model*> models);
	~Scene();

	std::vector<Model*> GetModels();
};
