#include "Chunk.hpp"

Chunk::Chunk(glm::ivec2 pos, ShaderPtr shader) : Renderable(shader), m_position(pos)
{
    proceduralGeneration();
    buildMesh();

    // testing
    m_model = glm::translate(m_model, glm::vec3{5, 0, -10});
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