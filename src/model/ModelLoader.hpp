#pragma once

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Vertex.hpp"
#include "Model.hpp"
#include "Mesh.hpp"

class ModelLoader {
private:
	static uint32_t currentVAOId;
	static uint32_t currentVBOId;
	static uint32_t currentEBOId;

	static void CreateAndBindVAO();
	static void CreateAndBindVBO();
	static void CreateAndBindEBO();
	static void UnbindVAO();

	static void AddVertexes(std::vector<Vertex>& vertexes);
	static void AddIndices(std::vector<uint32_t>& indices);

	static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes);
	static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

	static Model* CreateModel(Mesh* mesh);
public:
	static Model* LoadModelFromFile(std::string fileName);
};