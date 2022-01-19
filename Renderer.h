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
	
	enum UniformType
	{
		INT,
		FLOAT,
		VEC2,
		VEC3,
		VEC4,
		MAT4
	};

private:

	class UniformInput
	{
	public:
		template<typename T>
		UniformInput(GLuint location, UniformType type) : type(type), location(location)
		{
			switch (T)
			{
			case int:
				type = UniformType::INT;
				break;
			case float:
				type = UniformType::FLOAT;
				break;
			case glm::vec2:
				type = UniformType::VEC2;
				break;
			case glm::vec3:
				type = UniformType::VEC3;
				break;
			case glm::vec4:
				type = UniformType::VEC4;
				break;
			case glm::mat4:
				type = UniformType::MAT4;
				break;
			}
		}
		
		void Use(Shader shader)
		{
			switch (type)
			{
			case UniformType::INT:
				shader.SetInteger(location, *(int*) ptr);
				break;
			case UniformType::FLOAT:
				shader.SetFloat(location, *(float*)ptr);
				break;
			case UniformType::VEC2:
				shader.SetVector2f(location, *(glm::vec2*)ptr);
				break;
			case UniformType::VEC3:
				shader.SetVector3f(location, *(glm::vec3*)ptr);
				break;
			case UniformType::VEC4:
				shader.SetVector4f(location, *(glm::vec4*)ptr);
				break;
			case UniformType::MAT4:
				shader.SetMatrix4(location, *(glm::mat4*)ptr);
				break;
			}
		}


	private: 
		UniformType type;
		GLuint location;
		const void* ptr;
	};
	
	const Shader* _Shader;

	std::map<std::string, UniformInput> uniformCache;
	std::map<std::string, GLuint>::iterator cacheItr;

	template <typename T>
	void LoadUniform(const char* name);

	template <typename T>
	void SetUniformValue(const char* name, T value);

};

#endif //SPRITE_RENDERER_H