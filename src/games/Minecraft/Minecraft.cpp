#include "Minecraft.hpp"
#include <ResourceManager.hpp>

Minecraft::Minecraft() :
    Application(1280, 720)
{
}

void Minecraft::init()
{
    auto shader = ResourceManager::GetShader("VoxelShader", "src/shaders/vert.glsl", "src/shaders/frag.glsl");
    m_chunk = std::make_shared<Chunk>(glm::ivec2{0, 0}, shader);

    m_scene.addRenderable(m_chunk);
}

void Minecraft::update(double dt)
{

}

void Minecraft::renderUI()
{

}