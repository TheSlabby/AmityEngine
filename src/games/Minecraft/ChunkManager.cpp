#include "ChunkManager.hpp"
#include <print>

void ChunkManager::init(ShaderPtr shader)
{
    m_shader = shader;

    // create jthread
    m_workerThread = std::jthread([this](std::stop_token stop){
        worker(stop);
    });
}

void ChunkManager::newChunk(glm::ivec2 pos)
{
    ChunkPtr chunk = std::make_shared<Chunk>(pos, m_shader);
    m_chunks.push_back(chunk);

    std::println("new chunk made");
}

void ChunkManager::worker(std::stop_token stop)
{
    std::println("WORKER STARTED IN NEW THREAD!");
    while (!stop.stop_requested()) {
        std::println("xD");

        // wait for cv to signal
        std::unique_lock lock(m_mutex);
        m_cv.wait(lock, [this](){
            return !m_jobs.empty() || m_stopping.load();
        });
        if (m_stopping || stop.stop_requested()) break;

        std::println("DOING WORK!");
    }

}

void ChunkManager::shutdown()
{
    m_workerThread.request_stop();
    m_stopping.store(true);
    m_cv.notify_all();
}