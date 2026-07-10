#pragma once

#include <Entity.hpp>
#include <Scene.hpp>
#include <GLFW/glfw3.h>

using namespace Core;

class Player
{
public:
    Player(Scene& scene);

    void init(GLFWwindow* window);
    void update(double dt);

private:
    // MOUSE MOVEMENT
    void handleMouseInput(double dt);
    float  m_yaw        = -90.0f;   // -90 so you start looking down -Z, not off to +X
    float  m_pitch      =  0.0f;
    double m_lastMouseX =  0.0;
    double m_lastMouseY =  0.0;
    bool   m_firstMouse =  true;
    float  m_sensitivity = 0.15f;

    EntityPtr m_entity;
    Scene& m_scene;

    GLFWwindow* m_window;

};