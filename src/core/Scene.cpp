#include "Scene.hpp"

namespace Core {

void Scene::render(double dt)
{
    // uniforms

    for (const auto& renderable : m_renderables)
    {
        renderable->render(*this, dt);
    }
}

void Scene::update(double dt)
{
    // update logic
}

}