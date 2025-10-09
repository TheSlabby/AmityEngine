#include "TestGame.hpp"


TestGame::TestGame() : Application(1280, 720)
{
    m_appName = "Test Game";
}

void TestGame::init()
{
    std::cout << "app specific init" << std::endl;

    // TESTING CODE
    auto shader = std::make_shared<Shader>();


    // tree
    auto treeModel = std::make_shared<ModelRenderable>(ModelConfig{"C:/Users/walke/Desktop/Dev/AmityEngine/LowPolyAssets/Tree.glb", 20.0f, 2.0f}, shader);
    treeModel->setModelMatrix(glm::translate(treeModel->getModelMatrix(), glm::vec3(0.0, 10.0f, 0)));
    m_scene.addRenderable(treeModel);

    // terrain
    m_scene.addRenderable(std::make_shared<TerrainRenderable>(TerrainSettings{}, shader));

    // set shaders
    shader->setShader("shaders/vert.glsl", "shaders/frag.glsl"); // TODO figure out paths better (so it works on windows too)

    // setup projection
    shader->use();
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (static_cast<float>(WIDTH) / HEIGHT), 0.1f, 5000.0f);
    shader->setMat4("u_Proj", projection);

    // initial cam test pos
    m_scene.getCamera().moveTo(glm::vec3(0.0f, 200.0f, 500.0f));
    m_scene.getCamera().lookAt(glm::vec3{0});
    shader->setMat4("u_View", m_scene.getView());
}

void TestGame::update(double dt)
{
    // std::cout << "runtime: " << m_runTime << std::endl;
    // move camera in a circle
    Camera& cam = m_scene.getCamera();
    float circle_distance = 500;
    float circle_speed = 0.1f;
    cam.setX(glm::sin(m_runTime * circle_speed) * circle_distance);
    cam.setZ(glm::cos(m_runTime * circle_speed) * circle_distance);
    cam.lookAt(glm::vec3{});
}