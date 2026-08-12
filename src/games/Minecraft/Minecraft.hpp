#pragma once

#include <Application.hpp>
#include "ChunkManager.hpp"
#include "Player.hpp"

using namespace Core;

class Minecraft : public Application
{
public:
    Minecraft();

    void init() override;
    void update(double dt) override;
    void renderUI() override;

protected:
    void shutdown() override;

private:
    ChunkManager m_chunkManager;
    ChunkPtr m_chunk; // eventually itll be a list of chunks

    Player m_player;
    
};