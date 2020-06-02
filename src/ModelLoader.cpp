#include <iostream>
#include <cstdint>

#include "ModelLoader.hpp"
#include "PrimitiveModelLoader.hpp"

Model* ModelLoader::LoadModelFromFile(std::string fileName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Error loading model!" << importer.GetErrorString() << std::endl;
		return nullptr;
	}

    std::vector<Mesh*> meshes;
    ProcessNode(scene->mRootNode, scene, meshes);

    std::vector<glm::vec3> vertexPositions;
    for (auto vertex : meshes[0]->GetVertices())
    {
        vertexPositions.push_back(vertex.position);
    }

	return PrimitiveModelLoader::CreateModel(vertexPositions, meshes[0]->GetIndices());
}

void ModelLoader::ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene, meshes);
    }
}


Mesh* ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    for (uint32_t i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        if (mesh->mTextureCoords[0])
        {
            vertex.uvCoordinates.x = mesh->mTextureCoords[0][i].x;
            vertex.uvCoordinates.y = mesh->mTextureCoords[0][i].y;
        }
        else 
        {
            vertex.uvCoordinates.x = 0.0f;
            vertex.uvCoordinates.y = 0.0f;
        }

        vertices.push_back(vertex);
    }
    
    for (uint32_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        
        for (uint32_t j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    return new Mesh(vertices, indices);
}
