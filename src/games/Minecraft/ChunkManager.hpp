#pragma once

#include "Chunk.hpp"
#include <atomic>
#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>

class ChunkManager
{
public:
    ChunkManager() = default;
    void init(ShaderPtr shader);

    void newChunk(glm::ivec2 pos);

    void shutdown();


private:
    std::vector<ChunkPtr> m_chunks {};
    ShaderPtr m_shader;

    // worker thread
    std::jthread m_workerThread;
    void worker(std::stop_token stop);
    std::condition_variable m_cv;
    std::mutex m_mutex;
    std::queue<glm::ivec2> m_jobs;
    std::atomic<bool> m_stopping {false};

};
