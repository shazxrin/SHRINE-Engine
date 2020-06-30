#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "assets/Texture.hpp"
#include "assets/TextureLoader.hpp"
#include "assets/Scene.hpp"
#include "assets/Vertex.hpp"
#include "assets/Model.hpp"
#include "assets/Mesh.hpp"
#include "assets/Attribute.hpp"

class AssetLoader 
{
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

	static void ProcessNodes(aiNode* node, const aiScene* scene, std::vector<Model*>& outModels);
	static Model* GetModelFromNode(aiMesh* mesh, const aiScene* scene);
	static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	static Material* ProcessMaterial(aiMesh* mesh, const aiScene* scene);

	static Model* CreateModel(Mesh* mesh, Material* texture);
public:
	static Scene* Load3DAsset(std::string fileName);
};
