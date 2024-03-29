#include "AssetLoader.hpp"

uint32_t AssetLoader::currentVAOId = 0;
uint32_t AssetLoader::currentVBOId = 0;
uint32_t AssetLoader::currentEBOId = 0;

void AssetLoader::CreateAndBindVAO()
{
    glGenVertexArrays(1, &currentVAOId);
    glBindVertexArray(currentVAOId);
}

void AssetLoader::CreateAndBindVBO()
{
    glGenBuffers(1, &currentVBOId);
    glBindBuffer(GL_ARRAY_BUFFER, currentVBOId);
}


void AssetLoader::CreateAndBindEBO()
{
    glGenBuffers(1, &currentEBOId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentEBOId);
}

void AssetLoader::UnbindVAO()
{
    glBindVertexArray(0);
}

void AssetLoader::AddVertexes(std::vector<Vertex>& vertexes)
{
    std::vector<float> vertexBuffer = {};
    for (auto vertex : vertexes)
    {
        vertexBuffer.push_back(vertex.position.x);
        vertexBuffer.push_back(vertex.position.y);
        vertexBuffer.push_back(vertex.position.z);

        vertexBuffer.push_back(vertex.normal.x);
        vertexBuffer.push_back(vertex.normal.y);
        vertexBuffer.push_back(vertex.normal.z);

        vertexBuffer.push_back(vertex.uvCoordinates.x);
        vertexBuffer.push_back(vertex.uvCoordinates.y);
    }

    uint16_t stride = sizeof(float) * 8;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexBuffer.size(), vertexBuffer.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(Attribute::POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, stride, 0);
    glVertexAttribPointer(Attribute::NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glVertexAttribPointer(Attribute::UV_COORDS_LOCATION, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
}

void AssetLoader::AddIndices(std::vector<uint32_t>& indices)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

void AssetLoader::ProcessNodes(aiNode* node, const aiScene* scene, std::vector<Model*>& outModels)
{
    for (uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        outModels.push_back(GetModelFromNode(mesh, scene));
    }

    // Then do the same for each of its children.
    for (uint32_t i = 0; i < node->mNumChildren; i++)
    {
        ProcessNodes(node->mChildren[i], scene, outModels);
    }
}

Model* AssetLoader::GetModelFromNode(aiMesh* mesh, const aiScene* scene)
{
    Mesh* processedMesh = ProcessMesh(mesh, scene);
    Material* processedMaterial = ProcessMaterial(mesh, scene);

    Model* model = CreateModel(processedMesh, processedMaterial);

    return model;
}


Mesh* AssetLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
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

Material* AssetLoader::ProcessMaterial(aiMesh* mesh, const aiScene* scene)
{
    aiString path;

    scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &path);
    Texture* diffuse = nullptr;
    if (path.length > 0)
    {
        diffuse = TextureLoader::LoadTexture(path.C_Str());
    }

    return new Material(diffuse);
}

Model* AssetLoader::CreateModel(Mesh* mesh, Material* material)
{
    CreateAndBindVAO();

    CreateAndBindVBO();
    AddVertexes(mesh->GetVertexes());

    CreateAndBindEBO();
    AddIndices(mesh->GetIndices());

    Model* model = new Model(currentVAOId, currentVBOId, currentEBOId, mesh->GetIndices().size(), material);

    UnbindVAO();

    delete mesh;

    return model;
}

Scene* AssetLoader::Load3DAsset(std::string fileName)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "Error loading model!" << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    std::vector<Model*> models;
    ProcessNodes(scene->mRootNode, scene, models);

    return new Scene(models);
}
