#ifndef GENERAL_RENDERER_H
#define GENERAL_RENDERER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <typeinfo>

#include"VBO.h"
#include"VAO.h"
#include"EBO.h"
#include"Texture.h"
#include"Window.h"
#include <vector>

class GeneralRenderer
{
public:
	

	GeneralRenderer(const Shader& shader);
	

	GLuint GetUniformLoc(const char* name);
	void SetUniforms(bool useShader = false) const;

	/*Uniform Loaders
#pragma region Uniform Loaders

	void LoadFloat	(GLuint location, float value);
	void LoadInt	(GLuint location, int value);
	void LoadVec2f	(GLuint location, float x, float y);
	void LoadVec2f	(GLuint location, const glm::vec2& value);
	void LoadVec3f	(GLuint location, float x, float y, float z);
	void LoadVec3f	(GLuint location, const glm::vec3& value);
	void LoadVec4f	(GLuint location, float x, float y, float z, float w);
	void LoadVec4f	(GLuint location, const glm::vec4& value);
	void LoadMat4	(GLuint location, const glm::mat4& matrix);

	void LoadFloat	(const char* name, float value);
	void LoadInt	(const char* name, int value);
	void LoadVec2f	(const char* name, float x, float y);
	void LoadVec2f	(const char* name, const glm::vec2& value);
	void LoadVec3f	(const char* name, float x, float y, float z);
	void LoadVec3f	(const char* name, const glm::vec3& value);
	void LoadVec4f	(const char* name, float x, float y, float z, float w);
	void LoadVec4f	(const char* name, const glm::vec4& value);
	void LoadMat4	(const char* name, const glm::mat4& matrix);
	
#pragma endregion
*/
	void Render(const VAO& vertices, bool useShader = false, bool loadUniforms = false) const;

	template <typename DataT>
	void LoadUniform(const char* name);

	template <typename DataT>
	void SetUniformValue(GLuint loc, DataT value) { assert(false); }

	void SetUniformValue(GLuint loc, int value);
	void SetUniformValue(GLuint loc, float value);
	void SetUniformValue(GLuint loc, glm::vec2 value);
	void SetUniformValue(GLuint loc, glm::vec3 value);
	void SetUniformValue(GLuint loc, glm::vec4 value);
	void SetUniformValue(GLuint loc, glm::mat4 value);

	template <typename DataT>
	void SetUniformValue(const char* name, DataT value);

private:
	template<typename DataT>
	class UniformInput;
	enum ClassHashes;
	
	const Shader* _Shader;

	std::map<std::string, GLuint> uniformNameCache;

	std::map<GLuint, int> uniformIntCache;
	std::map<GLuint, float> uniformFloatCache;
	std::map<GLuint, glm::vec2> uniformVec2Cache;
	std::map<GLuint, glm::vec3> uniformVec3Cache;
	std::map<GLuint, glm::vec4> uniformVec4Cache;
	std::map<GLuint, glm::mat4> uniformMat4Cache;

	template<typename DataT>
	void SetCache(const std::map<GLuint, DataT>& values) const;

	template<typename DataT>
	void SetData(GLuint loc, DataT data) const { assert(false); }

	void SetData(GLuint loc, int data) const		{ this->_Shader->SetInteger(loc, data); }
	void SetData(GLuint loc, float data) const		{ this->_Shader->SetFloat(loc, data); }
	void SetData(GLuint loc, glm::vec2 data) const	{ this->_Shader->SetVector2f(loc, data); }
	void SetData(GLuint loc, glm::vec3 data) const	{ this->_Shader->SetVector3f(loc, data); }
	void SetData(GLuint loc, glm::vec4 data) const	{ this->_Shader->SetVector4f(loc, data); }
	void SetData(GLuint loc, glm::mat4 data) const	{ this->_Shader->SetMatrix4(loc, data); }
};

//template<typename DataT>
//class GeneralRenderer::UniformInput
//{
//public:
//	UniformInput(GLuint location) : location(location) {}
//
//	void setData(DataT value) { data = value }
//	DataT getData() const { return data;  }
//	GLuint getLoc() const { return location; }
//
//private: 
//	GLuint location;
//	DataT data;
//};

#endif