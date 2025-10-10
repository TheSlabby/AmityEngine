#include "Scene.hpp"

namespace Core {

void Scene::render(double dt)
{
    // render renderables
    for (const auto& renderable : m_renderables)
    {
        renderable->render(*this, dt);
    }

    // entities
    for (const auto& entity : m_entities)
    {
        // update entity 
        entity->translate(entity->getVelocity() * static_cast<float>(dt));

        entity->render(*this, dt);
    }
}

void Scene::update(double dt)
{
    // update logic
    glm::vec3 forwardVec = m_camera.forwardVector();
    glm::vec3 pos = m_camera.getPosition();
    glm::vec3 upVec{0.0f, 1.0f, 0.0f};
    ALfloat listenerOrientation[] = {
        forwardVec.x, forwardVec.y, forwardVec.z, upVec.x, upVec.y, upVec.z
    };
    alListenerfv(AL_ORIENTATION, listenerOrientation);
    alListener3f(AL_POSITION, pos.x, pos.y, pos.z);

}

}