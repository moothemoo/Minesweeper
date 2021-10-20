#include"SpriteSheet.h"

SpriteSheet::SpriteSheet(unsigned int numWidth, unsigned int numHeight, Texture2D& tex)
	: numSpritesX(numWidth),
	numSpritesY(numHeight),
	texture(&tex)
{
}

void SpriteSheet::GetTexLoc(GLfloat& left, GLfloat& right, GLfloat& top, GLfloat& bottom, unsigned int texID) const
{
	if (texID > numSpritesX * numSpritesY) {
		std::cout << "texID out of bounds: " << texID << std::endl;
		assert(false);
	}

	GLfloat xID = texID % numSpritesX;
	GLfloat yID = texID / numSpritesX;
	left = xID / numSpritesX;
	right = (xID + 1) / numSpritesX;
	top = (yID + 1) / numSpritesY;
	bottom = yID / numSpritesY;
}

const Texture2D& SpriteSheet::getTex() const
{
	return *texture;
}