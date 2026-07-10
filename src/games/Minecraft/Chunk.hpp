#pragma once

#include <Renderable.hpp>

using namespace Core;

class Chunk : public Renderable
{
public:
    Chunk(glm::ivec2 pos, ShaderPtr shader);

    void render(const Scene& scene, double dt) override;

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
    };

private:
    void proceduralGeneration();
    void buildMesh();

    glm::ivec2 m_position; // in 2d grid coords

    GLuint m_vao {0};
    GLuint m_vbo {0};
    GLsizei m_vertexCount {0};
    std::vector<Vertex> m_vertices {};

};
using ChunkPtr = std::shared_ptr<Chunk>;