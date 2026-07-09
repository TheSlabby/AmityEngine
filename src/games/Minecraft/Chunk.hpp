#pragma once

#include <Renderable.hpp>

using namespace Core;

class Chunk : public Renderable
{
public:
    Chunk(glm::ivec2 pos, ShaderPtr shader);

    void render(const Scene& scene, double dt) override;

private:
    glm::ivec2 m_position; // in 2d grid coords
    ShaderPtr m_shader;

};
using ChunkPtr = std::shared_ptr<Chunk>;