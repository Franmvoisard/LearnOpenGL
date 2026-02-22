#include "shader.hpp"

#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>

#include "glad/glad.h"

std::string get_file_contents(const std::string &filename) {

    std::ifstream fileInputStream;
    fileInputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // Open file
        fileInputStream.open(filename);
        std::stringstream fileContent;

        // Read content
        fileContent << fileInputStream.rdbuf();
        fileInputStream.close();
        return fileContent.str();
    }
    catch(std::ifstream::failure &exception)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ::" << exception.what() << std::endl;
    }
}

void Shader::SetFloatVector4(int uniformIndex, float v0, float v1, float v2, float v3) {
    glUniform4f(uniformIndex, v0, v1, v2, v3);
}

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode = get_file_contents(vertexPath);
    std::string fragmentCode = get_file_contents(fragmentPath);

    const char *vertexShaderSource = vertexCode.c_str();
    const char *fragmentShaderSource = fragmentCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create shader program and link shaders
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Use program and free shaders memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::SetInt(const std::string &name, int value) const {
    glUniform1i(GetUniformLocation(name.c_str()), value);
}

void Shader::SetBool(const std::string &name, bool value) const {
    glUniform1i(GetUniformLocation(name.c_str()), static_cast<int>(value));
}

void Shader::SetFloat(const std::string &name, float value) const {
    glUniform1f(GetUniformLocation(name.c_str()), value);
}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}

GLint Shader::GetUniformLocation(const char *str) const {
    const GLint uniformLocation = glGetUniformLocation(ID, str);
    if (uniformLocation == -1) {
        std::cout << "ERROR::SHADER::UNIFORM::NOT_FOUND::" << str  << std::endl;
        return -1;
    }
    return uniformLocation;
}