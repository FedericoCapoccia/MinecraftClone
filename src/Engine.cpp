#include "Engine.hpp"

#include <iostream>
#include <stdexcept>

namespace mc {

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
    s_WIDTH = width;
    s_HEIGHT = height;
}

void Engine::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(s_WIDTH, s_HEIGHT, m_title, nullptr, nullptr);
    if (!m_window) {
        throw std::runtime_error("Failed to initialize game window");
    }
    glfwMakeContextCurrent(m_window);
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    // FLAGS
    glEnable(GL_DEPTH_TEST);
}

void Engine::start() const
{
    while (!glfwWindowShouldClose(m_window)) {
        glClearColor(0.475f, 0.651f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        std::cout << "Window Dimensions: " << s_WIDTH << " x " << s_HEIGHT << std::endl;
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

}


}

// #include "Engine.hpp"
// #include "Camera.hpp"
// #include "Shader.hpp"
//
// #include <iostream>
// // clang-format off
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
//
// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>
//
// #include <glm/gtc/matrix_transform.hpp>
//
// // clang-format on
//
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void processInput(GLFWwindow* window);
// void mouse_callback(GLFWwindow* window, double xPos, double yPos);
// void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
//
// constexpr unsigned int WIDTH = 800;
// constexpr unsigned int HEIGHT = 600;
//
// Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// float lastX = WIDTH / 2.0;
// float lastY = HEIGHT / 2.0;
// bool firstMouse = true;
//
// float deltaTime = 0.0f;
// float lastFrame = 0.0f;
//
// int main()
// {
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//     GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Minecraft", nullptr, nullptr);
//     if (!window) {
//         std::cout << "Failed to create window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
//
//     // Glad init
//     if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
//         std::cout << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }
//
//     glViewport(0, 0, WIDTH, HEIGHT);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//     constexpr float vertices[] = {
//         -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
//         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//         -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//
//         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//         -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
//         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//
//         -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//         -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//         -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//         0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
//         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//
//         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//         -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
//         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
//     };
//     // clang-format on
//
//     constexpr unsigned int indices[] = {
//         3, 2, 1,
//         3, 1, 0
//     };
//
//     // Buffers
//     unsigned int vertexBufferObject, vertexArrayObject, elementBufferObject;
//     glGenVertexArrays(1, &vertexArrayObject);
//     glGenBuffers(1, &vertexBufferObject);
//     glGenBuffers(1, &elementBufferObject);
//
//     glBindVertexArray(vertexArrayObject);
//
//     // 0. copy our vertices array and indices in a buffer for OpenGL to use
//     glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//     // 1. then set the vertex attributes pointers
//     // Positions
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0));
//     glEnableVertexAttribArray(0);
//
//     // Texture Coordinates
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
//     glEnableVertexAttribArray(2);
//
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//     // uncomment this call to draw in wireframe polygons.
//     // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//     // Textures
//     stbi_set_flip_vertically_on_load(true);
//     unsigned int texture1, texture2;
//     glGenTextures(1, &texture1);
//
//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_2D, texture1);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//
//     int width, height, nrChannels;
//     void* data = stbi_load("resources/textures/container.jpg", &width, &height, &nrChannels, 0);
//
//     if (data) {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     } else {
//         std::cerr << "Failed to load texture" << std::endl;
//     }
//     stbi_image_free(data);
//
//     glGenTextures(1, &texture2);
//     glActiveTexture(GL_TEXTURE1);
//     glBindTexture(GL_TEXTURE_2D, texture2);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//
//     data = stbi_load("resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
//
//     if (data) {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     } else {
//         std::cerr << "Failed to load texture" << std::endl;
//     }
//     stbi_image_free(data);
//
//     const mc::Shader basicShader("resources/shaders/basic.glsl");
//     basicShader.use();
//     basicShader.setInt("texture1", 0);
//     basicShader.setInt("texture2", 1);
//
//     glEnable(GL_DEPTH_TEST);
//
//
//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//     glfwSetCursorPosCallback(window, mouse_callback);
//     glfwSetScrollCallback(window, scroll_callback);
//     while (!glfwWindowShouldClose(window)) {
//         const auto currentFrame = static_cast<float>(glfwGetTime());
//         deltaTime = currentFrame - lastFrame;
//         lastFrame = currentFrame;
//
//         processInput(window);
//
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//         /* Start Rendering */
//
//         const glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);
//         const glm::mat4 view = camera.GetViewMatrix();
//         basicShader.setMat4("projection", projection);
//         basicShader.setMat4("view", view);
//
//         constexpr auto model = glm::mat4(1.0f);
//         basicShader.setMat4("model", model);
//
//         // bind textures on corresponding texture units
//         glActiveTexture(GL_TEXTURE0);
//         glBindTexture(GL_TEXTURE_2D, texture1);
//         glActiveTexture(GL_TEXTURE1);
//         glBindTexture(GL_TEXTURE_2D, texture2);
//         basicShader.use();
//
//         glBindVertexArray(vertexArrayObject);
//         glDrawArrays(GL_TRIANGLES, 0, 36);
//
//         // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
//         // glDrawArrays(GL_TRIANGLES, 0, 36);
//
//         /* Stop Rendering */
//
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }
//
//     glDeleteVertexArrays(1, &vertexArrayObject);
//     glDeleteBuffers(1, &vertexBufferObject);
//     glDeleteBuffers(1, &elementBufferObject);
//
//     glfwTerminate();
//     return 0;
// }
//
// void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
// {
//     glViewport(0, 0, width, height);
// }
//
// void mouse_callback(GLFWwindow* window, const double xPos, const double yPos)
// {
//     const auto xPosOut = static_cast<float>(xPos);
//     const auto yPosOut = static_cast<float>(yPos);
//
//     if (firstMouse) {
//         lastX = xPosOut;
//         lastY = yPosOut;
//         firstMouse = false;
//     }
//
//     const float xOffset = xPosOut - lastX;
//     const float yOffset = lastY - yPosOut; // reversed since y-coordinates go from bottom to top
//
//     lastX = xPosOut;
//     lastY = yPosOut;
//
//     camera.ProcessMouseMovement(xOffset, yOffset);
// }
//
// void scroll_callback(GLFWwindow* window, const double xOffset, const double yOffset)
// {
//     camera.ProcessMouseScroll(static_cast<float>(yOffset));
// }
//
// void processInput(GLFWwindow* window)
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
//
//     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//         camera.ProcessKeyboard(FORWARD, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//         camera.ProcessKeyboard(BACKWARD, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//         camera.ProcessKeyboard(LEFT, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//         camera.ProcessKeyboard(RIGHT, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//         camera.ProcessKeyboard(UP, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//         camera.ProcessKeyboard(DOWN, deltaTime);
// }
