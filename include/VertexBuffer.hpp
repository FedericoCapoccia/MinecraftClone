#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace mc {

class VertexBuffer {
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    static void Unbind();
private:
    unsigned int m_RendererID {};
};

}

#endif
