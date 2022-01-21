#ifndef RENDERER_H
#define RENDERER_H

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

class Renderer
{
public:
	

	Renderer(const Shader& shader);
	

	GLuint GetUniformLoc(const char* name);
	void SetUniforms(bool useShader = false);

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
	void Render();

private:
	template<typename DataT>
	class UniformInput;
	enum ClassHashes;
	
	const Shader* _Shader;

	std::map<std::string, UniformInput<int>> uniformCache;
	std::map<std::string, UniformInput<float>> uniformCache;
	std::map<std::string, UniformInput<glm::vec2>> uniformCache;
	std::map<std::string, UniformInput<glm::vec3>> uniformCache;
	std::map<std::string, UniformInput<glm::vec4>> uniformCache;
	std::map<std::string, UniformInput<glm::mat4>> uniformCache;

	template <typename DataT>
	void LoadUniform(const char* name);

	template <typename DataT>
	void SetUniformValue(const char* name, DataT value);
};

template<typename DataT>
class Renderer::UniformInput
{
public:
	template<typename DataT> 
	UniformInput(GLuint location) : location(location) {}

private: 
	GLuint location;
	DataT data;
};

#endif //SPRITE_RENDERER_H