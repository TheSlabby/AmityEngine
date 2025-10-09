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
#include "Sound.hpp"
#include <AL/al.h>
#include <AL/alc.h>

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

    void setupProjectionMatrix();
    glm::mat4 m_projection;

    GLFWwindow* m_window;

    double m_lastFrameTime;
    double m_startTime;

    Scene m_scene;

    int WIDTH;
    int HEIGHT;
    
    double m_runTime { 0.0 };

    ALCdevice* device;
    ALCcontext* context;

    // resize callback
    static void onResizeCallback(GLFWwindow* window, int width, int height);
    void onResize(GLFWwindow* window, int width, int height);

};

} // Core namespace