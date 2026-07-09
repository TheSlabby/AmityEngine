#include "Chunk.hpp"

Chunk::Chunk(glm::ivec2 pos, ShaderPtr shader) : m_position(pos), Renderable(shader)
{

}

void Chunk::render(const Scene& scene, double dt)
{
    
}