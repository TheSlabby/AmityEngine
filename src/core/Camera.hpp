#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Core {

class Camera
{
public:
    Camera();

    void setX(float x) { m_pos.x = x; };
    void setY(float y) { m_pos.y = y; };
    void setZ(float z) { m_pos.z = z; };

    void moveTo(const glm::vec3& pos);

    void lookAt(const glm::vec3& pos);

    // getters
    glm::mat4 getView() const;
    glm::vec3 getPosition() const { return m_pos; }
    glm::vec3 forwardVector() const;

private:
    glm::vec3 m_pos{0.0f};
    glm::mat3 m_rotation{1.0f};
};

} // Core namespace