#include "Minecraft.hpp"
#include <ResourceManager.hpp>

Minecraft::Minecraft() :
    Application(1280, 720),
    m_player(m_scene)
{
}

void Minecraft::init()
{
    auto shader = ResourceManager::GetShader("VoxelShader", "src/shaders/vert.glsl", "src/shaders/frag.glsl");
    m_chunk = std::make_shared<Chunk>(glm::ivec2{0, 0}, shader);

    m_scene.addRenderable(m_chunk);

    m_player.init(m_window);
}

void Minecraft::update(double dt)
{
    m_player.update(dt);
}

void Minecraft::renderUI()
{

}