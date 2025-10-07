#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Renderable.hpp"
#include "Shader.hpp"

namespace Core {

class Application
{
public:
    Application(int width, int height);
    ~Application();

    virtual void init();

    int getWidth() { return WIDTH; }
    int getHeight() { return HEIGHT; }

    int run();

    virtual void update(double dt);

private:
    GLFWwindow* m_window;

    double m_lastFrameTime;

    // private constants
    int WIDTH;
    int HEIGHT;

    std::vector<Renderable> renderables;
};

} // Core namespace