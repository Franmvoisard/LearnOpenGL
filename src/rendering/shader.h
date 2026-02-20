#pragma once
#include <string>

#include "glad/glad.h"

std::string get_file_contents(const std::string& filename);
class Shader {
public:
    static void SetFloatVector4Uniform(int uniformIndex, float v0, float v1, float v2, float v3);
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);

    void Activate();
    void Delete();

    GLint GetUniformLocation(const char *str) const;
};


