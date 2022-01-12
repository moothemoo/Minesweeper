#ifndef RENDERER_H
#define RENDERER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"VBO.h"
#include"VAO.h"
#include"EBO.h"
#include"Texture.h"
#include"Window.h"

class Renderer
{
public:
	

	Renderer(const Shader& shader);
	

	GLuint GetUniformLoc(const char* name);
	void SetUniforms(bool useShader = false);

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

	void Render();
	
private:
	const Shader* _Shader;
	std::map<std::string, GLuint> uniformCache;
	std::map<std::string, GLuint>::iterator cacheItr;

	std::map<GLuint, float> floatUniforms;
	std::map<GLuint, float>::const_iterator floatItr;
	std::map<GLuint, int> intUniforms;
	std::map<GLuint, int>::const_iterator intItr;
	std::map<GLuint, glm::vec2> vec2Uniforms;
	std::map<GLuint, glm::vec2>::const_iterator vec2Itr;
	std::map<GLuint, glm::vec3> vec3Uniforms;
	std::map<GLuint, glm::vec3>::const_iterator vec3Itr;
	std::map<GLuint, glm::vec4> vec4Uniforms;
	std::map<GLuint, glm::vec4>::const_iterator vec4Itr;
	std::map<GLuint, glm::mat4> mat4Uniforms;
	std::map<GLuint, glm::mat4>::const_iterator mat4Itr;

};

#endif //SPRITE_RENDERER_H