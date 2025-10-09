#pragma once
#include "Camera.hpp"
#include "Renderable.hpp"

namespace Core {

// forward declaration
class Renderable;

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

    void addRenderable(std::shared_ptr<Renderable> renderable) { m_renderables.push_back(renderable); }

private:
    std::vector<std::shared_ptr<Renderable>> m_renderables;
    Camera m_camera;
};

}