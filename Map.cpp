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
	if (difficulty * width * height + 9 > width * height)
	{
		assert(false);
	}

	int xLoc, yLoc;
	renderer.getTile(xLoc, yLoc, firstClickX, firstClickY);
	bool xValid = xLoc >= 0 && xLoc < width;
	bool yValid = yLoc >= 0 && yLoc < height;
	if (!(xValid && yValid))
	{
		return;
	}

	int numMines = (int)(difficulty * width * height);
	MineArray = std::vector<int>(numMines);
	std::vector<int> mines(width * height);
	

	for (int i = 0; i < width * height; i++)
	{
		mines[i] = i;
	}

	std::shuffle(mines.begin(), mines.end(), std::default_random_engine(std::time(nullptr)));

	int offset = 0;
	int x, y;
	bool xSafe, ySafe;

	//std::cout << firstClickX << ", " << firstClickY << std::endl;

	for (int i = 0; i < numMines + offset; i++)
	{
		x = mines[i] % width;
		y = mines[i] / width;
		xSafe = (x <= xLoc + 1) && (x >= xLoc - 1);
		ySafe = (y <= yLoc + 1) && (y >= yLoc - 1);
		if (xSafe && ySafe)
		{
			offset++;
			//std::cout << x << ", " << y << std::endl;
			assert(offset < 9);
		}
		else
		{
			TileArray[x][y].mine = true;
			MineArray[i - offset] = mines[i - offset];
		}
		
		//std::cout << mines[i] << std::endl;
	}
}

bool Map::click(float mouseX, float mouseY)
{
	int xLoc, yLoc;
	renderer.getTile(xLoc, yLoc, mouseX, mouseY); 
	bool xValid = xLoc >= 0 && xLoc < width;
	bool yValid = yLoc >= 0 && yLoc < height;
	if (xValid && yValid && !TileArray[xLoc][yLoc].flagged) 
	{
		return this->uncover(xLoc, yLoc);
	}
	return false;
}

void Map::flag(float mouseX, float mouseY)
{
	int xLoc, yLoc;
	renderer.getTile(xLoc, yLoc, mouseX, mouseY);
	bool xValid = xLoc >= 0 && xLoc < width;
	bool yValid = yLoc >= 0 && yLoc < height;
	if (xValid && yValid && !TileArray[xLoc][yLoc].uncovered)
	{
		if (TileArray[xLoc][yLoc].flagged)
		{
			renderer.setTileTex(9, xLoc, yLoc);
		}
		else
		{
			renderer.setTileTex(11, xLoc, yLoc);
		}
		TileArray[xLoc][yLoc].flagged = !TileArray[xLoc][yLoc].flagged;
	}
}


bool Map::uncover(int xLoc, int yLoc)
{
	TileArray[xLoc][yLoc].uncovered = true;
	if (TileArray[xLoc][yLoc].mine)
	{
		renderer.setTileTex(10, xLoc, yLoc);
		return true;
	}
	else
	{
		int numMines = 0;
		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				bool xValid = xLoc + dx >= 0 && xLoc + dx < width;
				bool yValid = yLoc + dy >= 0 && yLoc + dy < height;
				if (xValid && yValid && TileArray[xLoc + dx][yLoc + dy].mine)
				{
					numMines++;
				}
			}
		}
		renderer.setTileTex(numMines, xLoc, yLoc);

		if (numMines == 0)
		{
			for (int dx = -1; dx <= 1; dx++)
			{
				for (int dy = -1; dy <= 1; dy++)
				{
					bool xValid = xLoc + dx >= 0 && xLoc + dx < width;
					bool yValid = yLoc + dy >= 0 && yLoc + dy < height;
					if (xValid && yValid && !TileArray[xLoc + dx][yLoc + dy].uncovered)
					{
						this->uncover(xLoc + dx, yLoc + dy);
					}
				}
			}
		}
	}
	return false;
}

void Map::Render(glm::mat4 projection)
{
	renderer.drawMap(projection);
}

void Map::revealMines()
{
	for (int i = 0; i < MineArray.size(); i++)
	{
		this->uncover(MineArray[i] % width, MineArray[i] / width);
	}
}