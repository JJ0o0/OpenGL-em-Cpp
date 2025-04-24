#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>

class Shader
{
private:
    unsigned int program;

    std::string loadShaderSource(const std::string& filePath);
    std::string vertex_shader_src;
    std::string frag_shader_src;

    unsigned int compileShader(const char* shaderCode, GLenum shaderT);
    unsigned int createShaderProgram(const char* vertexShader, const char* fragmentShader);
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    bool load();

    unsigned int getProgram() const;
};


#endif