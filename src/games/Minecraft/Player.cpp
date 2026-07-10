#include "Player.hpp"

Player::Player(Scene& scene) :
    m_scene(scene)
{
    // setup player entity
    m_entity = std::make_shared<Entity>();
    m_entity->addComponent<CameraComponent>();
}

void Player::init(GLFWwindow* window)
{
    m_window = window;
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Player::update(double dt)
{
    handleMouseInput(dt);
    m_scene.setCameraEntity(m_entity);
}

// Player::handleMouseInput is vibecoded ngl (TODO revisit this)
void Player::handleMouseInput(double dt)
{
    // only look around when the cursor is captured (set via GLFW_CURSOR_DISABLED)
    if (glfwGetInputMode(m_window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
    {
        m_firstMouse = true;   // re-seed when we regain capture, so no snap
        return;
    }

    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);

    // first captured frame: seed last-pos so we don't jump from a stale value
    if (m_firstMouse)
    {
        m_lastMouseX = xpos;
        m_lastMouseY = ypos;
        m_firstMouse = false;
    }

    double dx = xpos - m_lastMouseX;
    double dy = m_lastMouseY - ypos;   // reversed: screen-Y grows down, pitch grows up
    m_lastMouseX = xpos;
    m_lastMouseY = ypos;

    dx *= m_sensitivity;
    dy *= m_sensitivity;

    m_yaw   += static_cast<float>(dx);
    m_pitch += static_cast<float>(dy);
    m_pitch  = std::clamp(m_pitch, -89.0f, 89.0f);   // no flip at the poles

    // rebuild the look direction and point the entity there
    glm::vec3 front;
    front.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    front.y = std::sin(glm::radians(m_pitch));
    front.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    front = glm::normalize(front);

    if (m_entity)
        m_entity->lookAt(m_entity->getPosition() + front);
}