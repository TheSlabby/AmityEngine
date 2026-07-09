#pragma once

#include <Application.hpp>
#include "Chunk.hpp"

using namespace Core;

class Minecraft : public Application
{
public:
    Minecraft();

    void init() override;
    void update(double dt) override;
    void renderUI() override;

private:
    ChunkPtr m_chunk; // eventually itll be a list of chunks
    
};