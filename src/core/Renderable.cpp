#include "Renderable.hpp"

namespace Core {

// THIS IS TEMPORARY TEST WITH A CUBE! later we need to use assimp for actual meshes

// Cube vertices (positions only for now)
float vertices[] = {
    // positions
   -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
   -0.5f,  0.5f, -0.5f,
   -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f,  0.5f
};

// Cube indices
unsigned int indices[] = {
    0,1,2, 2,3,0,  // back
    4,5,6, 6,7,4,  // front
    0,4,7, 7,3,0,  // left
    1,5,6, 6,2,1,  // right
    3,2,6, 6,7,3,  // top
    0,1,5, 5,4,0   // bottom
};

Renderable::Renderable(std::shared_ptr<Shader> shader) : m_shader(shader), m_model(glm::mat4(1.0f))
{
    m_shader->setMat4("u_Model", m_model);

    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO); // bind VAO

    // glGenBuffers(1, &VBO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind VBO
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // put vertices in VBO

    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // bind EBO
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // put indices in EBO

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
}

void Renderable::render(double dt) const
{
    // m_shader->use();
    // m_shader->setMat4("u_Model", m_model);
    // m_model = glm::rotate(m_model, static_cast<float>(dt), glm::vec3(0, 1.0, 0));
    // glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // unbind
}



}