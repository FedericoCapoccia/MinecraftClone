#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace mc {

class IndexBuffer {
public:
    IndexBuffer(const unsigned char* data, int count);
    ~IndexBuffer();

    void Bind() const;
    static void Unbind() ;

    [[nodiscard]] int GetCount() const { return m_Count; }
private:
    unsigned int m_RendererID = 0;
    int m_Count;
};

}

#endif
