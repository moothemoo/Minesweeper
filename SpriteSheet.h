#ifndef SPRITE_SHEET_H
#define SPRITe_SHEET_H


#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include"Texture.h"


class SpriteSheet
{
public:
	SpriteSheet(unsigned int numWidth, unsigned int numHeight, Texture2D& tex);
	void GetTexLoc(GLfloat& left, GLfloat& right, GLfloat& top, GLfloat& bottom, unsigned int texID) const;
	const Texture2D& getTex() const;
protected:
	unsigned int numSpritesX, numSpritesY;
	Texture2D* texture;
};

#endif