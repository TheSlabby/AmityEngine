#pragma once

#include <Renderable.hpp>
#include <array>

using namespace Core;

class Chunk : public Renderable
{
public:
    Chunk(glm::ivec2 pos, ShaderPtr shader);
    ~Chunk();
    
    void render(const Scene& scene, double dt) override;

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
    };

    // constants
    static constexpr int CHUNK_SIZE = 16;
    static constexpr int CHUNK_HEIGHT = 128;

    // directions
    static constexpr std::array<glm::ivec3, 6> DIRECTIONS = {{
        {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}
    }};

    // face tris
    static constexpr std::array<std::array<glm::vec3, 6>, 6> FACE_TEMPLATES = {{
        {{ {1,0,1},{1,0,0},{1,1,1}, {1,1,1},{1,0,0},{1,1,0} }},  // +X
        {{ {0,0,0},{0,0,1},{0,1,0}, {0,1,0},{0,0,1},{0,1,1} }},  // -X
        {{ {0,1,1},{1,1,1},{0,1,0}, {0,1,0},{1,1,1},{1,1,0} }},  // +Y
        {{ {0,0,0},{1,0,0},{0,0,1}, {0,0,1},{1,0,0},{1,0,1} }},  // -Y
        {{ {0,0,1},{1,0,1},{0,1,1}, {0,1,1},{1,0,1},{1,1,1} }},  // +Z
        {{ {1,0,0},{0,0,0},{1,1,0}, {1,1,0},{0,0,0},{0,1,0} }},  // -Z
    }};

private:
    void proceduralGeneration();
    void buildVertices();
    void buildMesh();

    glm::ivec2 m_position; // in 2d grid coords

    GLuint m_vao {0};
    GLuint m_vbo {0};
    GLsizei m_vertexCount {0};
    std::vector<Vertex> m_vertices {};

    // BLOCKS ARRAY
    std::array<std::array<std::array<uint8_t, CHUNK_SIZE>, CHUNK_HEIGHT>, CHUNK_SIZE> m_blocks;

};
using ChunkPtr = std::shared_ptr<Chunk>;