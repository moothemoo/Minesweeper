#include"GeneralRenderer.h"
GeneralRenderer::GeneralRenderer(const Shader& shader)
    : _Shader(&shader)
{
    uniformIntCache = std::map<GLuint, int>();
    uniformFloatCache = std::map<GLuint, float>();
    uniformVec2Cache = std::map<GLuint, glm::vec2>();
    uniformVec3Cache = std::map<GLuint, glm::vec3>();
    uniformVec4Cache = std::map<GLuint, glm::vec4>();
    uniformMat4Cache = std::map<GLuint, glm::mat4>();
}

void GeneralRenderer::Render(const VAO& vertices, bool useShader, bool loadUniforms) const
{
    if (loadUniforms)
    {
        SetUniforms(useShader);
    }
    else if (useShader)
    {
        _Shader->Use();
    }

    glBindVertexArray(vertices.ID);
    glDrawArrays(GL_TRIANGLES, 0, vertices.GetVBOSize());
    glBindVertexArray(0);
}

GLuint GeneralRenderer::GetUniformLoc(const char* name)
{/*
    cacheItr = uniformCache.find(name);
    if (cacheItr == uniformCache.end())
    {
        uniformCache[name] = glGetUniformLocation(_Shader->ID, name);
        return uniformCache[name];
    }
    return cacheItr->second;*/
}

void GeneralRenderer::SetUniforms(bool useShader) const
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


template<typename DataT>
void GeneralRenderer::LoadUniform(const char* name)
{   
    unsigned long long typeHash = typeid(DataT).hash_code();
    switch(typeHash)
    {
        case typeid(int).hash_code() :
            uniformIntCache[name] = UniformInput<int>(_Shader.getUniformLoc(name));
            return;
        case typeid(float).hash_code():
            uniformFloatCache[name] = UniformInput<float>(_Shader.getUniformLoc(name));
            return;
        case typeid(glm::vec2).hash_code():
            uniformVec2Cache[name] = UniformInput<glm::vec2>(_Shader.getUniformLoc(name));
            return;
        case typeid(glm::vec3).hash_code():
            uniformVec2Cache[name] = UniformInput<glm::vec3>(_Shader.getUniformLoc(name));
            return;
        case typeid(glm::vec4).hash_code():
            uniformVec2Cache[name] = UniformInput<glm::vec4>(_Shader.getUniformLoc(name));
            return;
        case typeid(glm::mat4).hash_code():
            uniformVec2Cache[name] = UniformInput<glm::mat4>(_Shader.getUniformLoc(name));
            return;
    }
    assert(false);
}

void GeneralRenderer::SetUniformValue(GLuint loc, int value)         { uniformIntCache[loc] = value; }
void GeneralRenderer::SetUniformValue(GLuint loc, float value)       { uniformFloatCache[loc] = value; }
void GeneralRenderer::SetUniformValue(GLuint loc, glm::vec2 value)   { uniformVec2Cache[loc] = value; }
void GeneralRenderer::SetUniformValue(GLuint loc, glm::vec3 value)   { uniformVec3Cache[loc] = value; }
void GeneralRenderer::SetUniformValue(GLuint loc, glm::vec4 value)   { uniformVec4Cache[loc] = value; }
void GeneralRenderer::SetUniformValue(GLuint loc, glm::mat4 value)   { uniformMat4Cache[loc] = value; }

template <typename DataT>
void GeneralRenderer::SetUniformValue(const char* name, DataT value) 
{ 
    this->SetUniformValue(uniformNameCache[name], value); 
}

template<typename DataT>
void GeneralRenderer::SetCache(const std::map<GLuint, DataT>& values) const
{
    typename std::map<GLuint, DataT>::const_iterator itr;
    for (itr = values.begin(); itr != values.end(); itr++)
    {
        this->SetData(itr->first, itr->second);
    }
}
