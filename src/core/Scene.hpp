#pragma once
#include "Camera.hpp"
#include "Renderable.hpp"
#include "Entity.hpp"
#include <AL/al.h>
#include <vector>

namespace Core {

// forward declaration
class Renderable;
class Entity;

class Scene
{
public:
    // Scene();

    // render loop
    void render(double dt);

    // update loop
    virtual void update(double dt);

    // getters
    Camera& getCamera() { return m_camera; }
    glm::mat4 getView() const { return m_camera.getView(); }
    glm::mat4 getProjection() const { return m_projection; }

    void setProjectionMatrix(glm::mat4 p) { m_projection = p; }

    void addRenderable(std::shared_ptr<Renderable> renderable) { m_renderables.push_back(renderable); }
    void addEntity(std::shared_ptr<Entity> entity) { m_entities.push_back(entity); }

private:
    glm::mat4 m_projection;
    std::vector<std::shared_ptr<Renderable>> m_renderables;
    std::vector<std::shared_ptr<Entity>> m_entities;
    Camera m_camera;
};

}