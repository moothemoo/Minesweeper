#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

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

class SpriteRenderer
{
public:
	

	SpriteRenderer(Shader& shader, GLfloat* vertices, unsigned int vertSize, GLuint* indices, unsigned int indexSize);


	void drawSprite(Texture2D& tex, glm::vec2 loc, float angle, glm::vec2 scale, glm::vec3 color);
	
private:
	VAO _VAO;
	VBO _VBO;
	EBO _EBO;
	Shader _Shader;

	unsigned int indSize;
};

#endif //SPRITE_RENDERER_H