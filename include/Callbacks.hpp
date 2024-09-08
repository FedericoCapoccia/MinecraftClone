#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

namespace mc {

inline void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
    s_WIDTH = width;
    s_HEIGHT = height;
}

inline void mouse_callback(GLFWwindow* window, const double xPos, const double yPos)
{
    const auto xPosOut = static_cast<float>(xPos);
    const auto yPosOut = static_cast<float>(yPos);

    if (firstMouse) {
        lastX = xPosOut;
        lastY = yPosOut;
        firstMouse = false;
    }

    const float xOffset = xPosOut - lastX;
    const float yOffset = lastY - yPosOut; // reversed since y-coordinates go from bottom to top

    lastX = xPosOut;
    lastY = yPosOut;

    camera.ProcessMouseMovement(xOffset, yOffset);
}

inline void scroll_callback(GLFWwindow* window, const double xOffset, const double yOffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yOffset));
}

inline void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

}

#endif // CALLBACKS_HPP
