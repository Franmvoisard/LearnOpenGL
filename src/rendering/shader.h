#pragma once
#include <string>

std::string get_file_contents(const std::string& filename);

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);

    void Activate();
    void Delete();
};


