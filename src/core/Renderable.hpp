#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <filesystem>
#include "Shader.hpp"

namespace Core {

class Renderable
{
public:
    Renderable(std::shared_ptr<Shader> shader);

    void render(double dt) const;

private:
    GLuint VAO, VBO, EBO;
    std::shared_ptr<Shader> m_shader;
    mutable glm::mat4 m_model;
};

}