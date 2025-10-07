#include "Application.hpp"

namespace Core {

Application::Application(int width, int height) : WIDTH(width), HEIGHT(height), m_lastFrameTime(glfwGetTime())
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

    m_window = glfwCreateWindow(WIDTH, HEIGHT, "AmityEngine", nullptr, nullptr);
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

}

Application::~Application()
{
    // cleanup
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Application::init()
{
    std::cout << "app specific init" << std::endl;

    // TESTING CODE
    auto shader = std::make_shared<Shader>();
    shader->setShader("shaders/vert.glsl", "shaders/frag.glsl"); // TODO figure out paths better (so it works on windows too)
    shader->use();
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (800.0f / 600.0f), 0.1f, 100.0f);
    shader->setMat4("u_Proj", projection);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::inverse(glm::translate(view, glm::vec3(0.0f, -1.0f, 5.0f)));
    shader->setMat4("u_View", view);

    // test init
    renderables.emplace_back(shader);
}

int Application::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        // get deltatime
        double t = glfwGetTime();
        double dt = t - m_lastFrameTime;
        m_lastFrameTime = t;

        update(dt);

        // draw renderables
        for (const Renderable& renderable : renderables)
        {
            renderable.render(dt);
        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    return 0;
}

void Application::update(double dt)
{
    glClearColor(0.1, 0.1, 0.1,  1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


} // Core namespace