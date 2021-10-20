#ifndef TILE_RENDERER_H
#define TILE_RENDERER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"VBO.h"
#include"VAO.h"
#include"EBO.h"
#include"Texture.h"

class TileRenderer
{
public:


	TileRenderer(Shader& shader, const VAO& vaoIn);


	void drawTile(const Texture2D& tex, glm::vec2 loc) const;

private:
	const VAO* _VAO;
	Shader* _Shader;
};

#endif //TILE_RENDERER_H