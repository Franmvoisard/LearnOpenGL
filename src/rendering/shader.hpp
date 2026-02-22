#pragma once
#include <string>

#include "glad/glad.h"

std::string get_file_contents(const std::string& filename);
class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);

    void SetInt(const std::string &name, int value) const;
    void SetBool(const std::string &name, bool value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetFloatVector4(int uniformIndex, float v0, float v1, float v2, float v3);
    void Activate();
    void Delete();

    GLint GetUniformLocation(const char *str) const;
};


