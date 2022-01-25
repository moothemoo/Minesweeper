#include"Renderer.h"
Renderer::Renderer(const Shader& shader)
    : _Shader(&shader)
{
}

GLuint Renderer::GetUniformLoc(const char* name)
{/*
    cacheItr = uniformCache.find(name);
    if (cacheItr == uniformCache.end())
    {
        uniformCache[name] = glGetUniformLocation(_Shader->ID, name);
        return uniformCache[name];
    }
    return cacheItr->second;
*/}

void Renderer::SetUniforms(bool useShader) const
{
    SetCache<int>(&uniformIntCache);
}


template<typename DataT>
void Renderer::LoadUniform(const char* name)
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

void Renderer::SetUniformValue(GLuint loc, int value)         { uniformIntCache[loc] = value; }
void Renderer::SetUniformValue(GLuint loc, float value)       { uniformFloatCache[loc] = value; }
void Renderer::SetUniformValue(GLuint loc, glm::vec2 value)   { uniformVec2Cache[loc] = value; }
void Renderer::SetUniformValue(GLuint loc, glm::vec3 value)   { uniformVec3Cache[loc] = value; }
void Renderer::SetUniformValue(GLuint loc, glm::vec4 value)   { uniformVec4Cache[loc] = value; }
void Renderer::SetUniformValue(GLuint loc, glm::mat4 value)   { uniformMat4Cache[loc] = value; }

template <typename DataT>
void Renderer::SetUniformValue(const char* name, DataT value) 
{ 
    this->SetUniformValue(uniformNameCache[name], value); 
}

template<typename DataT>
void Renderer::SetCache(std::map<GLuint, DataT>& values) const
{
    typename std::map<GLuint, DataT>::const_iterator itr;
    for (itr = values.begin(); itr < values.end(); itr++)
    {
        this->SetData(itr->first, itr->second);
    }
}
