#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <iostream>
#include <string>

namespace mc {

class Shader {
public:
    unsigned int ProgramId = 0;

    explicit Shader(const char* filepath);
    ~Shader() { glDeleteProgram(ProgramId); }

    void use() const;
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private:
    void createShader(const std::string& vertShader, const std::string& fragShader);
};

}

#endif