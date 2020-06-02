#pragma once

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.hpp"
#include "Mesh.hpp"

class ModelLoader {
public:
	static Model* LoadModelFromFile(std::string fileName);
	static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes);
	static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
};