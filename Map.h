#ifndef MAP_H
#define MAP_H

#include"Tile.h"
#include"MapRenderer.h"

class Map
{
public:
	Map() {}
	Map(unsigned int width, unsigned int height, unsigned int defTexID, const SpriteSheet& spriteSheet, const Shader& shader);
	void Render(glm::mat4 projection);

	void loadMines(float difficulty, float firstClickX, float firstClickY);

	void click(int mouseX, int mouseY);

	void clickWorld(float mouseX, float mouseY);

private:
	std::vector<std::vector<Tile>> TileArray;
	unsigned int width, height;
	float tileWidth = 0.2f;
	float tileHeight = 0.2f;
	MapRenderer renderer;
};


#endif