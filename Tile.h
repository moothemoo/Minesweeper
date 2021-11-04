#ifndef TILE_H
#define TILE_H

#include"Texture.h"
#include"ResourceManager.h"

class Tile
{
public:
	Tile();
	Tile(unsigned int ID);
	bool mine = false;
protected:
	unsigned int tileID;
};

#endif