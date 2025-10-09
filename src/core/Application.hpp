#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "ModelRenderable.hpp"
#include "TerrainRenderable.hpp"
#include "Shader.hpp"
#include "Scene.hpp"

namespace Core {

class Application
{
public:
    Application(int width, int height);
    ~Application();

    virtual void init() = 0;

    int getWidth() { return WIDTH; }
    int getHeight() { return HEIGHT; }

    int run();

    virtual void update(double dt) = 0;

protected:
    std::string m_appName{"Engine Core"};
    glm::vec4 m_clearColor{0.1f, 0.1f, 0.1f, 1.0f};

    GLFWwindow* m_window;

    double m_lastFrameTime;
    double m_startTime;

    Scene m_scene;

    int WIDTH;
    int HEIGHT;
    
    double m_runTime { 0.0 };

};

} // Core namespace