#include "Chunk.hpp"
#include <random>

Chunk::Chunk(glm::ivec2 pos, ShaderPtr shader) : Renderable(shader), m_position(pos)
{
    proceduralGeneration();
    buildVertices(); // build m_vertices based on m_blocks

    // THIS IS GPU WORK so it must go on main thread
    buildMesh();

    // testing
    m_model = glm::translate(m_model, glm::vec3{5, 0, -10});
}

Chunk::~Chunk()
{
    if (m_vao != 0) glDeleteVertexArrays(1, &m_vao);
    if (m_vbo != 0) glDeleteBuffers(1, &m_vbo);
}

void Chunk::render(const Scene& scene, double dt)
{
    if (m_vertexCount == 0) return; // nothing meshed yet

    m_shader->use();

    // uniforms
    m_shader->setMat4("u_Model", m_model);
    m_shader->setMat4("u_View", scene.getView());
    m_shader->setMat4("u_Proj", scene.getProjection());
    m_shader->setMat3("u_NormalMatrix", glm::transpose(glm::inverse(glm::mat3(m_model))));

    // color
    m_shader->setVec4("u_MaterialColor", glm::vec4(0.35f, 0.65f, 0.30f, 1.0f));
    m_shader->setInt("u_HasTexture", 0);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
    glBindVertexArray(0); // unbind vao
}

void Chunk::buildMesh()
{
    // clear up old VAO/VBO
    if (m_vao) { glDeleteVertexArrays(1, &m_vao);   m_vao = 0; }
    if (m_vbo) { glDeleteBuffers(1, &m_vbo);        m_vbo = 0; }

    // create VAO/VBO
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    // bind so we can copy vertices to it
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // copy m_vertices to the gpu
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_DYNAMIC_DRAW);

    // attrib pointer is how to parse the bufferData
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    m_vertexCount = static_cast<GLsizei>(m_vertices.size());
    glBindVertexArray(0);
}

void Chunk::proceduralGeneration()
{
    // A single unit cube spanning (0,0,0)..(1,1,1).
    // 6 faces * 2 triangles * 3 verts = 36 vertices. { {position}, {normal} }
    // Winding is CCW-from-outside so GL_CULL_FACE (enabled globally) keeps them.
    m_vertices = {
        // Front (+Z)
        {{0,0,1},{0,0,1}}, {{1,0,1},{0,0,1}}, {{0,1,1},{0,0,1}},
        {{0,1,1},{0,0,1}}, {{1,0,1},{0,0,1}}, {{1,1,1},{0,0,1}},
        // Back (-Z)
        {{1,0,0},{0,0,-1}}, {{0,0,0},{0,0,-1}}, {{1,1,0},{0,0,-1}},
        {{1,1,0},{0,0,-1}}, {{0,0,0},{0,0,-1}}, {{0,1,0},{0,0,-1}},
        // Left (-X)
        {{0,0,0},{-1,0,0}}, {{0,0,1},{-1,0,0}}, {{0,1,0},{-1,0,0}},
        {{0,1,0},{-1,0,0}}, {{0,0,1},{-1,0,0}}, {{0,1,1},{-1,0,0}},
        // Right (+X)
        {{1,0,1},{1,0,0}}, {{1,0,0},{1,0,0}}, {{1,1,1},{1,0,0}},
        {{1,1,1},{1,0,0}}, {{1,0,0},{1,0,0}}, {{1,1,0},{1,0,0}},
        // Top (+Y)
        {{0,1,1},{0,1,0}}, {{1,1,1},{0,1,0}}, {{0,1,0},{0,1,0}},
        {{0,1,0},{0,1,0}}, {{1,1,1},{0,1,0}}, {{1,1,0},{0,1,0}},
        // Bottom (-Y)
        {{0,0,0},{0,-1,0}}, {{1,0,0},{0,-1,0}}, {{0,0,1},{0,-1,0}},
        {{0,0,1},{0,-1,0}}, {{1,0,0},{0,-1,0}}, {{1,0,1},{0,-1,0}},
    };
}

// build vertices based off of m_blocks, DO CULLING!
void Chunk::buildVertices()
{
    m_vertices.clear();

    // random m_blocks for esting purspoes
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                static std::random_device rd;
                static std::mt19937 gen(rd());
                static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
                if (dis(gen) > 0.8) {
                    m_blocks[x][y][z] = 1;
                } else {
                    m_blocks[x][y][z] = 0; 
                }
            }
        }
    }

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                auto blockID = m_blocks[x][y][z];
                if (blockID == 0) continue; // skip air
                
                glm::ivec3 pos {x, y, z};
                // RENDER A FACE IF IT IS VISIBLE!
                // so we have to check 6 directions: +x, -x, +y, -y, +z, -z
                for (int i = 0; i < DIRECTIONS.size(); ++i) {
                    bool shouldDrawFace = false;
                    const auto& dir = DIRECTIONS[i];
                    glm::ivec3 neighbor = pos + dir;
                    // check oob (if edge of chunk, it will be a face)
                    if (
                        (neighbor.x >= CHUNK_SIZE || neighbor.x < 0) ||
                        (neighbor.y >= CHUNK_HEIGHT || neighbor.y < 0) ||
                        (neighbor.z >= CHUNK_SIZE || neighbor.z < 0)
                    ) {
                        shouldDrawFace = true;
                    }
                    // check if neighbor is air (if so, its exposed, so draw face)
                    else if (m_blocks[neighbor.x][neighbor.y][neighbor.z] == 0) { 
                        shouldDrawFace = true;
                    }

                    if (shouldDrawFace)
                    {
                        // get face template
                        const auto& faceTemplate = FACE_TEMPLATES[i];
                        for (const auto& vertices : faceTemplate) {
                            Vertex v;
                            v.Normal = dir;
                            v.Position = {
                                glm::vec3(pos) + vertices,
                            };
                            m_vertices.push_back(v);
                        }
                    }
                }
            }
        }
    }
}