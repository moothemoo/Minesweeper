#include"Renderer.h"
Renderer::Renderer(const Shader& shader)
    : _Shader(&shader)
{
    uniformIntCache = std::map<GLuint, int>();
    uniformFloatCache = std::map<GLuint, float>();
    uniformVec2Cache = std::map<GLuint, glm::vec2>();
    uniformVec3Cache = std::map<GLuint, glm::vec3>();
    uniformVec4Cache = std::map<GLuint, glm::vec4>();
    uniformMat4Cache = std::map<GLuint, glm::mat4>();
}

void Renderer::Render(const VAO& vertices, bool useShader, bool loadUniforms) const
{
    if (loadUniforms)
    {
        SetUniforms(useShader);
    }
    else if (useShader)
    {
        _Shader->Use();
    }

    vertices.Bind();

    glDrawArrays(GL_TRIANGLES, 0, vertices.GetNumVertices());

    vertices.Unbind();
}

GLuint Renderer::GetUniformLoc(const char* name)
{
    std::map<std::string, GLuint>::iterator cacheItr = uniformNameCache.find(name);
    if (cacheItr == uniformNameCache.end())
    {
        uniformNameCache[name] = glGetUniformLocation(_Shader->ID, name);
        return uniformNameCache[name];
    }
    return cacheItr->second;
}

void Renderer::SetUniforms(bool useShader) const
{
    if (useShader)
    {
        _Shader->Use();
    }

    SetCache<int>(uniformIntCache);
    SetCache<float>(uniformFloatCache);
    SetCache<glm::vec2>(uniformVec2Cache);
    SetCache<glm::vec3>(uniformVec3Cache);
    SetCache<glm::vec4>(uniformVec4Cache);
    SetCache<glm::mat4>(uniformMat4Cache);
}




void Renderer::SetUniformValue(GLuint loc, int value)         { uniformIntCache[loc] = value; }
void Renderer::SetUniformValue(GLuint loc, float value)       { uniformFloatCache[loc] = value; }
void Renderer::SetUniformValue(GLuint loc, glm::vec2 value)   { uniformVec2Cache[loc] = value; }
void Renderer::SetUniformValue(GLuint loc, glm::vec3 value)   { uniformVec3Cache[loc] = value; }
void Renderer::SetUniformValue(GLuint loc, glm::vec4 value)   { uniformVec4Cache[loc] = value; }
void Renderer::SetUniformValue(GLuint loc, glm::mat4 value)   { uniformMat4Cache[loc] = value; }




