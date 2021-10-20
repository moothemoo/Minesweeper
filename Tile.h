#ifndef TILE_H
#define TILE_H

#include"Texture.h"
#include"ResourceManager.h"

class Tile
{
public:
	Tile();
	Tile(char ID);
protected:
	unsigned int tileID;
};

#endif