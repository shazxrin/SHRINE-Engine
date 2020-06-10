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

#include "texture/Texture.hpp"
#include "texture/TextureLoader.hpp"
#include "geometry/Vertex.hpp"
#include "geometry/Model.hpp"
#include "geometry/Mesh.hpp"
#include "geometry/Attribute.hpp"

class ModelLoader 
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

	static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes, std::vector<Texture*>& textures);
	static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	static Texture* ProcessTexture(aiMesh* mesh, const aiScene* scene);

	static Model* CreateModel(Mesh* mesh, Texture* texture);
public:
	static Model* LoadModelFromFile(std::string fileName);
};
