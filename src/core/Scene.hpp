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
    ~Scene();

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

    void setScreenSize(int width, int height);
    void setupFramebuffer();

private:
    glm::mat4 m_projection;
    std::vector<std::shared_ptr<Renderable>> m_renderables;
    std::vector<std::shared_ptr<Entity>> m_entities;
    Camera m_camera;


    GLuint m_fbo{0};
    GLuint m_colorTexture{0};
    GLuint m_depthBuffer{0};
    int m_fboWidth{800};
    int m_fboHeight{600}; 
};

}