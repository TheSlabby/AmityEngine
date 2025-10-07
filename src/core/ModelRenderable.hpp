#pragma once
#include "Renderable.hpp"
#include <vector>
#include <glad/glad.h>
#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace Core {

// structs
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};
struct Texture
{
    unsigned int id;
    std::string type;
};


// MESH CLASS
class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
        : vertices(vertices), indices(indices), textures(textures)
    {
        setupMesh();
    }
    void draw();
private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    GLuint VAO, VBO, EBO;

    void setupMesh();

}; // MESH CLASS



// MODEL RENDERABLE 
class ModelRenderable : public Renderable
{
public:
    ModelRenderable(const std::string& modelPath, std::shared_ptr<Shader> shader);
    void render(double dt) const override;


private:
    std::vector<std::unique_ptr<Mesh>> meshes;
    void processNode(aiNode *node, const aiScene *scene);
    void loadModel(const std::string& path);
    std::unique_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
};

    
} // Core namespace