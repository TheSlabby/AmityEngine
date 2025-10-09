#include "Camera.hpp"

namespace Core {

Camera::Camera()
{

}

void Camera::lookAt(const glm::vec3& pos)
{
    m_rotation = glm::inverse(glm::lookAt(m_pos, pos, glm::vec3(0.0f, 1.0f, 0.0f))); // lookAt inverses, so we need to inverse again
}

void Camera::moveTo(const glm::vec3& pos)
{
    m_pos = pos;
}

glm::mat4 Camera::getView() const
{
    glm::mat3 inverseRotation = glm::transpose(m_rotation); // inverse of rotation matrix is just transpose
    glm::vec3 invTranslation = -(inverseRotation * m_pos); // go OTHER direction (opposite: negative)
    glm::mat4 view = glm::mat4(inverseRotation);
    view[3] = glm::vec4(invTranslation, 1.0f);

    return view;
}

glm::vec3 Camera::forwardVector() const
{
    return -m_rotation[2];
}

}