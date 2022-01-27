#ifndef RENDERER_H
#define RENDERER_H


class Renderer
{
public:

	Renderer(const Shader& shader);


	GLuint GetUniformLoc(const char* name);
	void SetUniforms(bool useShader = false) const;
	void Render(bool useShader = false, bool loadUniforms = false);

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
};


#endif