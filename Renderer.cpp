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

void Renderer::SetUniforms(bool useShader)
{
    if (useShader)
    {
        _Shader->Use();
    }
    cacheItr = uniformCache.begin();
    
}

template<typename DataT>
void Renderer::LoadUniform(const char* name)
{   
    uniformCache[name] = UniformInput<DataT>(_Shader.getUniformLoc(name));
}

template <typename DataT>
void Renderer::SetUniformValue(const char* name, DataT value)
{
    uniformCache[name].setData(value);
}

