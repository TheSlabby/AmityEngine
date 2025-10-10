#include "Entity.hpp"

namespace Core {

void Entity::render(const Scene& scene, double dt)
{
    if (m_renderable)
    {
        this->updateRenderableModelMatrix();
        m_renderable->render(scene, dt);
    }
}

void Entity::updateRenderableModelMatrix()
{
    if (m_renderable)
    {
        glm::mat4 model = glm::translate(glm::mat4{1.0f}, m_position);
        model = model * glm::mat4(m_rotation);
        m_renderable->setModelMatrix(model);
    }
}

void Entity::rotate(float angle, glm::vec3 axis)
{
    m_rotation = glm::rotate(glm::mat4(m_rotation), angle, axis); 
}

}