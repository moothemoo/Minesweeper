#ifndef TILE_H
#define TILE_H

#include"Texture.h"
#include"ResourceManager.h"

class Tile
{
public:
	Tile();
	Tile(unsigned int ID);
protected:
	unsigned int tileID;
	bool mine = false;
};

#endif