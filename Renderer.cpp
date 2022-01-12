#include"Renderer.h"
Renderer::Renderer(const Shader& shader)
    : _Shader(&shader)
{
}

GLuint Renderer::GetUniformLoc(const char* name)
{
    cacheItr = uniformCache.find(name);
    if (cacheItr == uniformCache.end())
    {
        uniformCache[name] = glGetUniformLocation(_Shader->ID, name);
        return uniformCache[name];
    }
    return cacheItr->second;
}

void Renderer::SetUniforms(bool useShader = false)
{
	floatItr = floatUniforms.begin();

}

#pragma region Uniform Loaders
void Renderer::LoadFloat(GLuint location, float value)
{
	floatUniforms[location] = value;
}
void Renderer::LoadInt(GLuint location, int value)
{
	intUniforms[location] = value;
}
void Renderer::LoadVec2f(GLuint location, float x, float y)
{
	this->LoadVec2f(location, glm::vec2(x, y));
}
void Renderer::LoadVec2f(GLuint location, const glm::vec2& value)
{
	vec2Uniforms[location] = value;
}
void Renderer::LoadVec3f(GLuint location, float x, float y, float z)
{
	this->LoadVec3f(location, glm::vec3(x, y, z));
}
void Renderer::LoadVec3f(GLuint location, const glm::vec3& value)
{
	vec3Uniforms[location] = value;
}
void Renderer::LoadVec4f(GLuint location, float x, float y, float z, float w)
{
	this->LoadVec4f(location, glm::vec4(x, y, z, w));
}
void Renderer::LoadVec4f(GLuint location, const glm::vec4& value)
{
	vec4Uniforms[location] = value;
}
void Renderer::LoadMat4(GLuint location, const glm::mat4& matrix)
{
	mat4Uniforms[location] = matrix;
}

void Renderer::LoadFloat(const char* name, float value)
{
	LoadFloat(this->GetUniformLoc(name), value);
}
void Renderer::LoadInt(const char* name, int value)
{
	LoadFloat(this->GetUniformLoc(name), value);
}
void Renderer::LoadVec2f(const char* name, float x, float y)
{
	LoadVec2f(this->GetUniformLoc(name), glm::vec2(x, y));
}
void Renderer::LoadVec2f(const char* name, const glm::vec2& value)
{
	LoadVec2f(this->GetUniformLoc(name), value);
}
void Renderer::LoadVec3f(const char* name, float x, float y, float z)
{
	LoadVec2f(this->GetUniformLoc(name), glm::vec3(x, y, z));
}
void Renderer::LoadVec3f(const char* name, const glm::vec3& value)
{
	LoadVec3f(this->GetUniformLoc(name), value);
}
void Renderer::LoadVec4f(const char* name, float x, float y, float z, float w)
{
	LoadVec4f(this->GetUniformLoc(name), glm::vec4(x, y, z, w));
}
void Renderer::LoadVec4f(const char* name, const glm::vec4& value)
{
	LoadVec4f(this->GetUniformLoc(name), value);
}
void Renderer::LoadMat4(const char* name, const glm::mat4& matrix)
{
	LoadMat4(this->GetUniformLoc(name), matrix);
}
#pragma endregion