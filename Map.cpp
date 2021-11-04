#include"Map.h"

#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine

int getInt(std::stringstream& stream);

Map::Map(unsigned int width, unsigned int height, unsigned int defTexID, const SpriteSheet& spriteSheet, const Shader& shader)
	:width(width), height(height),
	renderer(spriteSheet, shader, tileWidth, tileHeight)
{
	renderer.init(width, height, defTexID);

	TileArray = std::vector<std::vector<Tile>>(width, std::vector<Tile>(height, Tile(defTexID)));
}

int getInt(std::stringstream& stream)
{
	int out = (stream.get() << 24);
	out = out | (stream.get() << 16);
	out = out | (stream.get() << 8);
	out = out | (stream.get());
	return out;
}


void Map::loadMines(float difficulty, float firstClickX, float firstClickY)
{
	std::cout << "e" << std::endl;
	if (difficulty > 1)
	{
		assert(false);
	}

	int numMines = (int)(difficulty * width * height);
	std::vector<bool> mines(width * height, false);
	for (int i = 0; i < numMines; i++)
	{
		mines[i] = true;
	}
	std::shuffle(mines.begin(), mines.end(), std::default_random_engine());
	for (int i = 0; i < width * height; i++)
	{
		TileArray[i % width][i / width].mine = mines[i];
	}
}

void Map::clickWorld(float mouseX, float mouseY)
{
	int xLoc, yLoc;
	renderer.getTile(xLoc, yLoc, mouseX, mouseY);
	
}

void Map::click(int mouseX, int mouseY)
{
	if (TileArray[mouseX][mouseY].mine)
	{
		renderer.setTileTex(10, mouseX, mouseY);
	}
	else
	{
		int numMines = 0;
		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				bool xValid = mouseX + dx >= 0 && xLoc + dx < width;
				bool yValid = mouseY + dy >= 0 && mouseY + dy < height;
				if (xValid && yValid && TileArray[xLoc + dx][mouseY + dy].mine)
				{
					numMines++;
				}
			}
		}
		renderer.setTileTex(numMines, mouseX, mouseY);

		if (numMines == 0)
		{
			for (int dx = -1; dx <= 1; dx++)
			{
				for (int dy = -1; dy <= 1; dy++)
				{
					bool xValid = mouseY + dx >= 0 && xLoc + dx < width;
					bool yValid = yLoc + dy >= 0 && yLoc + dy < height;
					if (xValid && yValid)
					{
					}
				}
			}
		}
	}
}

void Map::Render(glm::mat4 projection)
{
	renderer.drawMap(projection);
}