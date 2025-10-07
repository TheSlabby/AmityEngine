#include "ModelRenderable.hpp"

namespace Core {

// MESH
void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // vertex normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    // texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // release VAO
}

void Mesh::draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // release VAO
}
// END MESH


ModelRenderable::ModelRenderable(const std::string& modelPath, std::shared_ptr<Shader> shader) : Renderable(shader)
{
    m_model = glm::scale(m_model, glm::vec3(0.001f));
    loadModel(modelPath);
}

void ModelRenderable::loadModel(const std::string& path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ASSIMP ERROR: " << import.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
}

void ModelRenderable::processNode(aiNode *node, const aiScene *scene)
{
    // process all meshes in node
    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    // recurse
    for (unsigned int i = 0; i < node->mNumChildren; ++i)
    {
        processNode(node->mChildren[i], scene);
    }
}

std::unique_ptr<Mesh> ModelRenderable::processMesh(aiMesh *mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;
        glm::vec3 vector{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
        vertex.Position = vector;
        // normals
        if (mesh->HasNormals())
        {
            glm::vec3 normal{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
            vertex.Normal = normal;   
        }
        //texture coords
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 textureVec{mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
            vertex.TexCoords = textureVec;
        }
        else
        {
            vertex.TexCoords = glm::vec2{0.0f, 0.0f};
        }

        vertices.push_back(vertex);
    }

    // faces/indices
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    return std::make_unique<Mesh>(vertices, indices, textures);
}

void ModelRenderable::render(double dt) const
{
    m_shader->use();
    m_shader->setMat4("u_Model", m_model);
    for (const auto& mesh : meshes)
    {
        mesh->draw();
    }
}


}