#ifndef ENGINE_HPP
#define ENGINE_HPP

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace mc {

inline int s_WIDTH = 0;
inline int s_HEIGHT = 0;

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

}

#endif
