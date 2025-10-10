#pragma once
#include "Renderable.hpp"
#include "Scene.hpp"
#include <memory>

namespace Core {


// forward declaration
class Renderable;
class Scene;


class Entity
{
public:

    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getVelocity() const { return m_velocity; }
    Renderable* getRenderable() { return m_renderable.get(); }

    void setPosition(glm::vec3 pos) { m_position = pos; }
    void setVelocity(glm::vec3 vel) { m_velocity = vel; }
    void translate(glm::vec3 offset) { m_position += offset; }
    void rotate(float angle, glm::vec3 axis);
    void setRenderable(std::shared_ptr<Renderable> r) { m_renderable = r; }


    void render(const Scene& scene, double dt);


private:
    glm::vec3 m_position{0.0f};
    glm::vec3 m_velocity{0.0f};
    glm::mat3 m_rotation{1.0f};
    std::shared_ptr<Renderable> m_renderable;

    void updateRenderableModelMatrix();
};

}