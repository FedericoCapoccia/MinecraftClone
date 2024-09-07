#include "Shader.hpp"

#include <fstream>
#include <sstream>

namespace mc {

static unsigned int CompileShader(unsigned int type, const std::string& source);

enum ShaderType {
    NONE = -1,
    VERTEX,
    FRAGMENT
};

Shader::Shader(const char* filepath)
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

void Shader::createShader(const std::string& vertShader, const std::string& fragShader)
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

unsigned int CompileShader(const unsigned int type, const std::string& source)
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

void Shader::use() const
{
    glUseProgram(ProgramId);
}

void Shader::setBool(const std::string& name, const bool value) const
{
    glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, const int value) const
{
    glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, const float value) const
{
    glUniform1f(glGetUniformLocation(ProgramId, name.c_str()), value);
}

}