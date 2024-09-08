#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Camera.hpp"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace mc {

inline int s_WIDTH = 0;
inline int s_HEIGHT = 0;

inline Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
inline float lastX = static_cast<float>(s_WIDTH) / 2.0f;
inline float lastY = static_cast<float>(s_HEIGHT) / 2.0f;
inline bool firstMouse = true;
inline float deltaTime = 0.0f;
inline float lastFrame = 0.0f;

class Engine {
public:
    Engine(const int width, const int height, const char* title)
        : m_title(title)
    {
        s_WIDTH = width;
        s_HEIGHT = height;
        initWindow();
    }
    void start() const;

private:
    GLFWwindow* m_window {};
    const char* m_title;
    void initWindow();
};

// clang-format off
constexpr float vertices[] = {
    -1,  1,  1,
    -1, -1,  1,
     1, -1,  1,
     1,  1,  1,
    -1,  1, -1,
    -1, -1, -1,
     1, -1, -1,
     1,  1, -1,
};

constexpr unsigned char indices[] = {
    0, 1, 2, 0, 2, 3, // front
    3, 2, 6, 3, 6, 7, // right
    7, 6, 5, 7, 5, 4, // back
    4, 5, 1, 4, 1, 0, // left
    4, 0, 3, 4, 3, 7, // top
    1, 5, 6, 1, 6, 2, // bottom
};

// clang-format on

}

#endif
