#include "Application.hpp"

namespace Core {

Application::Application(int width, int height) : WIDTH(width), HEIGHT(height), m_lastFrameTime(glfwGetTime())
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }
    
    m_startTime = glfwGetTime();

    m_window = glfwCreateWindow(WIDTH, HEIGHT, m_appName.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        std::cerr << "Couldn't create window :(" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);

    // glad init
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // glDepthFunc(GL_LESS); // default; passes if the incoming depth value is less than the stored one


}

Application::~Application()
{
    // cleanup
    glfwDestroyWindow(m_window);
    glfwTerminate();
}


int Application::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        // get deltatime
        double t = glfwGetTime();
        double dt = t - m_lastFrameTime;
        m_lastFrameTime = t;
        m_runTime = t - m_startTime;

        // update (maybe move this to separate timer later)
        m_scene.update(dt);
        update(dt);

        // RENDER
        glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_scene.render(dt);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    return 0;
}



} // Core namespace