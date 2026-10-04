#pragma once
#include "Renderable.hpp"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "DataStructures.hpp"


namespace Core {


// MESH CLASS
class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, glm::vec4 materialColor)
        : vertices(vertices), indices(indices), textures(textures), materialColor(materialColor)
    {
        setupMesh();
    }
    ~Mesh();
    
    // disable copying
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    // moving
    Mesh(Mesh&&) noexcept;
    Mesh& operator=(Mesh&&) noexcept;


    void draw();

    glm::vec4 getMaterialColor() const { return materialColor; }
    const std::vector<Texture>& getTextures() const { return textures; }
    const std::vector<Vertex>& getVertices() const { return vertices; }
    const std::vector<unsigned int>& getIndices() const { return indices; }

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    glm::vec4 materialColor;

    GLuint VAO = 0, VBO = 0, EBO = 0;

    void setupMesh();

}; // MESH CLASS





// MODEL RENDERABLE 
class ModelRenderable : public Renderable
{
public:
    ModelRenderable(const ModelConfig& modelConfig, std::shared_ptr<Shader> shader);
    ~ModelRenderable();

    // owns GL textures, so no copying (Assimp::Importer isn't movable either)
    ModelRenderable(const ModelRenderable&) = delete;
    ModelRenderable& operator=(const ModelRenderable&) = delete;
    ModelRenderable(ModelRenderable&&) = delete;
    ModelRenderable& operator=(ModelRenderable&&) = delete;

    void render(const Scene& scene, double dt) override;
    const std::vector<std::unique_ptr<Mesh>>& getMeshes() const { return meshes; }

private:
    std::vector<std::unique_ptr<Mesh>> meshes;
    void processNode(aiNode *node, const aiScene *scene);
    void loadModel();
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName, const aiScene* scene);
    std::unique_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
    ModelConfig m_config;

    Assimp::Importer m_importer;
    std::vector<Texture> texturesLoaded; // cache textures
};

    
} // Core namespace