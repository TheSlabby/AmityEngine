#include "Scene.hpp"
#include "CollisionEntity.hpp"
#include <GLFW/glfw3.h>

namespace Core {

Scene::~Scene()
{
    if (glfwGetCurrentContext()) { // if using GLFW
        glDeleteFramebuffers(1, &m_fbo);
        glDeleteTextures(1, &m_colorTexture);
        glDeleteRenderbuffers(1, &m_depthBuffer);
    }
}

// render main image to this FBO, so we can do postprocessing
void Scene::setupFramebuffer()
{
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // Create color texture
    glGenTextures(1, &m_colorTexture);
    glBindTexture(GL_TEXTURE_2D, m_colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_fboWidth, m_fboHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTexture, 0);

    // Create depth buffer
    glGenRenderbuffers(1, &m_depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_fboWidth, m_fboHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);

    // Check framebuffer completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "ERROR: Framebuffer not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Scene::render(double dt)
{
    // RENDER TO FRAMEBUFFER
    // glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // render renderables (if not in entity, probably just a static render (like terrain player doesnt interact with))
    for (const auto& renderable : m_renderables)
    {
        renderable->render(*this, dt);
    }

    // entities
    for (const auto& entity : m_entities)
    {
        entity->render(*this, dt);
    }

    // unbind fbo
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

    // update entities
    for (const auto& entity : m_entities)
    {
        // velocity
        entity->translate(entity->getVelocity() * static_cast<float>(dt));
        // force (acceleration)
        entity->setVelocity(entity->getVelocity() + entity->getForce() * static_cast<float>(dt));


        // perform physics operations
        if (auto physicsEntity = std::dynamic_pointer_cast<CollisionEntity>(entity))
        {
            // TODO physics
        }
    }

}

void Scene::setScreenSize(int width, int height)
{
    m_fboWidth = width;
    m_fboHeight = height;
    setupFramebuffer();
}

}