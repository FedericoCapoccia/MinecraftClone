#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace mc {

class Texture {
public:
    Texture()
    {
        glGenTextures(1, &m_TextureID);
        glActiveTexture(GL_TEXTURE0);

    }
    void Bind() const
    {
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }

    static void Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    static void Load(const std::string& filename, const GLenum format)
    {
        int width, height, nrChannels;
        void* data = stbi_load(("resources/textures/" + filename).c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cerr << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

private:
    unsigned int m_TextureID = 0;
};

}

#endif
