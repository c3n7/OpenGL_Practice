#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>

class Shader {
  public:
    // the program id
    unsigned int programID;

    // constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
};
#endif