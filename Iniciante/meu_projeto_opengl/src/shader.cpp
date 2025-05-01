#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    vertex_shader_src = loadShaderSource(vertexPath);
    frag_shader_src = loadShaderSource(fragmentPath);
}

std::string Shader::loadShaderSource(const std::string& filePath) {
    std::ifstream s_file;
    std::stringstream s_stream;

    s_file.open(filePath);
    if (!s_file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de shader: " << filePath << std::endl;

        return "";
    }
    
    s_stream << s_file.rdbuf();
    s_file.close();

    return s_stream.str();
}

bool Shader::load() {
    program = createShaderProgram(vertex_shader_src.c_str(), frag_shader_src.c_str());

    return program != 0;
}

unsigned int Shader::compileShader(const char* shaderCode, GLenum shaderType) {
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infolog[512];
        glGetShaderInfoLog(shader, 512, NULL, infolog);
        std::cerr << "Erro de compilação do shader:\n" << infolog << std::endl;
    }
    
    return shader;
}

unsigned int Shader::createShaderProgram(const char* vertexShader, const char* fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Erro de linkagem do shader program:\n" << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int Shader::getProgram() const {
    return program;
}