#include "shader.h"

const Shader& Shader::Use() const
{
    glUseProgram(this->ID);
    return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
    unsigned int sVertex, sFragment, gShader;
    // vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    // fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    // shader program
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->ID, gShader);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

#pragma region Set Uniform with name
void Shader::SetFloat(const char* name, float value, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetInteger(const char* name, int value, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetVector2f(const char* name, float x, float y, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}
#pragma endregion
#pragma region Set Uniform with location
void Shader::SetFloat(const GLuint location, float value, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform1f(location, value);
}
void Shader::SetInteger(const GLuint location, int value, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform1i(location, value);
}
void Shader::SetVector2f(const GLuint location, float x, float y, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform2f(location, x, y);
}
void Shader::SetVector2f(const GLuint location, const glm::vec2& value, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform2f(location, value.x, value.y);
}
void Shader::SetVector3f(const GLuint location, float x, float y, float z, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform3f(location, x, y, z);
}
void Shader::SetVector3f(const GLuint location, const glm::vec3& value, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform3f(location, value.x, value.y, value.z);
}
void Shader::SetVector4f(const GLuint location, float x, float y, float z, float w, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform4f(location, x, y, z, w);
}
void Shader::SetVector4f(const GLuint location, const glm::vec4& value, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniform4f(location, value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const GLuint location, const glm::mat4& matrix, bool useShader) const
{
    if (useShader)
        this->Use();
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
}
#pragma endregion


void Shader::Delete()
{
    glDeleteProgram(this->ID);
}

GLuint Shader::getUniformLoc(const char* name)
{
    return glGetUniformLocation(this->ID, name);
}



void Shader::checkCompileErrors(unsigned int object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}
