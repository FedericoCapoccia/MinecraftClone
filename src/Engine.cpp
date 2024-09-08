#include "Engine.hpp"

#include "Callbacks.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexBuffer.hpp"

#include <glm/glm.hpp>
#include <iostream>

#include <stdexcept>

namespace mc {

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
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(m_window, mouse_callback);
    glfwSetScrollCallback(m_window, scroll_callback);

    // FLAGS
    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Engine::start() const
{
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const VertexBuffer vb(vertices, sizeof(vertices));
    const IndexBuffer ib(indices, 36);

    // layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    VertexBuffer::Unbind();
    IndexBuffer::Unbind();

    // Texture dirt block
    stbi_set_flip_vertically_on_load(true);
    const Texture textureBottom;
    textureBottom.Bind();
    Texture::Load("dirt.png", GL_RGBA);
    // Texture::Unbind();

    const Shader shader("resources/shaders/cube.glsl");
    shader.Bind();
    shader.setInt("Texture", 0);

    while (!glfwWindowShouldClose(m_window)) {
        // Delta time and input management
        const auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(m_window);

        // Render setup
        glClearColor(0.475f, 0.651f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Shader matrix injection
        const glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(s_WIDTH) / static_cast<float>(s_HEIGHT), 0.1f, 100.0f);
        const glm::mat4 view = camera.GetViewMatrix();
        auto model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(.25));
        shader.setMat4("model", model);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // Drawing
        ib.Bind();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_BYTE, reinterpret_cast<void*>(0));

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

}

