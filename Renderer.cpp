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
	
}

template<typename T>
void Renderer::LoadUniform(const char* name)
{   
    uniformCache[name] = UniformInput<T>(_Shader.getUniformLoc(name));
}

