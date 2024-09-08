#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace mc {

enum ShaderType {
    NONE = -1,
    VERTEX,
    FRAGMENT
};

class Shader {
public:
    unsigned int ProgramId = 0;

    explicit Shader(const char* filepath)
    {
        std::ifstream shaderFile(filepath);

        if (!shaderFile.is_open()) {
            std::cerr << "Unable to open shader file: " << filepath << std::endl;
        }

        ShaderType sType = NONE;
        std::stringstream shaderBuilders[2];

        std::string line;
        while (std::getline(shaderFile, line)) {
            if (line.find("//shader") == std::string::npos) {
                shaderBuilders[sType] << line << '\n';
                continue;
            }

            if (line.find("vertex") != std::string::npos) {
                sType = VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                sType = FRAGMENT;
            }
        }

        if (shaderFile.bad()) {
            std::cerr << "Error while reading file: " << filepath << std::endl;
        }
        shaderFile.close();

        const std::string vertexCode = shaderBuilders[VERTEX].str();
        const std::string fragmentCode = shaderBuilders[FRAGMENT].str();
        createShader(vertexCode, fragmentCode);
    }
    ~Shader() { glDeleteProgram(ProgramId); }

    void Bind() const
    {
        glUseProgram(ProgramId);
    }

    static void Unbind()
    {
        glUseProgram(0);
    }

    void setBool(const std::string& name, const bool value) const
    {
        glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), static_cast<int>(value));
    }

    void setInt(const std::string& name, const int value) const
    {
        glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), value);
    }

    void setFloat(const std::string& name, const float value) const
    {
        glUniform1f(glGetUniformLocation(ProgramId, name.c_str()), value);
    }
    void setMat4(const std::string& name, glm::mat4 value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ProgramId, name.c_str()), 1, GL_FALSE, value_ptr(value));
    }

private:
    void createShader(const std::string& vertShader, const std::string& fragShader)
    {
        const unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertShader);
        const unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragShader);
        ProgramId = glCreateProgram();

        glAttachShader(ProgramId, vertex);
        glAttachShader(ProgramId, fragment);
        glLinkProgram(ProgramId);
        glValidateProgram(ProgramId);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    static unsigned int CompileShader(const unsigned int type, const std::string& source)
    {
        const unsigned int id = glCreateShader(type);
        const char* src = source.c_str();

        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char message[length];
            glGetShaderInfoLog(id, length, &length, message);

            std::cerr << "Failed to compile "
                      << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                      << " shader: "
                      << message;
            glDeleteShader(id);
            return 0;
        }
        return id;
    }
};

}

#endif