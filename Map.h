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

	bool uncover(int mouseX, int mouseY);
	void flag(float mouseX, float mouseY);
	bool click(float mouseX, float mouseY);

	void revealMines();

private:
	std::vector<std::vector<Tile>> TileArray;
	std::vector<int> MineArray;
	unsigned int width, height;
	float tileWidth = 0.05f;
	float tileHeight = 0.05f;
	MapRenderer renderer;
};


#endif