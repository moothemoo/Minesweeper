#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <map>


class Shader
{
public:
    // state
    unsigned int ID;


    // constructor
    Shader() {  }
    // sets the current shader as active
    const Shader& Use() const;
    // compiles the shader from given source code
    void    Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); // note: geometry source code is optional 


    // utility functions

    GLuint getUniformLoc(const char* name) const;
    
    void    SetFloat(const char* name, float value, bool useShader = false) const;
    void    SetInteger(const char* name, int value, bool useShader = false) const;
    void    SetVector2f(const char* name, float x, float y, bool useShader = false) const;
    void    SetVector2f(const char* name, const glm::vec2& value, bool useShader = false) const;
    void    SetVector3f(const char* name, float x, float y, float z, bool useShader = false) const;
    void    SetVector3f(const char* name, const glm::vec3& value, bool useShader = false) const;
    void    SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false) const;
    void    SetVector4f(const char* name, const glm::vec4& value, bool useShader = false) const;
    void    SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false) const;

    void    SetFloat(const GLuint location, float value, bool useShader = false) const;
    void    SetInteger(const GLuint location, int value, bool useShader = false) const;
    void    SetVector2f(const GLuint location, float x, float y, bool useShader = false) const;
    void    SetVector2f(const GLuint location, const glm::vec2& value, bool useShader = false) const;
    void    SetVector3f(const GLuint location, float x, float y, float z, bool useShader = false) const;
    void    SetVector3f(const GLuint location, const glm::vec3& value, bool useShader = false) const;
    void    SetVector4f(const GLuint location, float x, float y, float z, float w, bool useShader = false) const;
    void    SetVector4f(const GLuint location, const glm::vec4& value, bool useShader = false) const;
    void    SetMatrix4(const GLuint location, const glm::mat4& matrix, bool useShader = false) const;

    void Delete();
private:
    // checks if compilation or linking failed and if so, print the error logs
    void    checkCompileErrors(unsigned int object, std::string type);
};

#endif