#include"Map.h"

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

void Map::click(float mouseX, float mouseY)
{
	int xLoc, yLoc;
	renderer.getTile(xLoc, yLoc, mouseX, mouseY);
	renderer.setTileTex(0, xLoc, yLoc);
}

void Map::Render(glm::mat4 projection)
{
	renderer.drawMap(projection);
}