#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "TileRenderer.h"
#include "VAO.h"
#include "VBO.h"
#include "SpriteSheet.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Map
{
public:
	Map(std::string file, const SpriteSheet& spriteSheet, const Shader& shader);
	Map(std::string file, const SpriteSheet& spriteSheet, const Shader& shader, GLfloat TileWidth, GLfloat TileHeight);

	const Tile& getTile(unsigned int x, unsigned int y) const;

	void drawMap() const;

	const VAO& getVAO();

private:
	int width, height;
	std::vector<std::vector<Tile>> TileArray;
	std::vector<GLfloat> vertexArray;
	VAO _VAO;
	VBO _VBO;
	const SpriteSheet* _sSheet;
	const Shader* _Shader;

	GLfloat TileWidth = 1.0f;
	GLfloat TileHeight = 1.0f;

	std::stringstream readMapFile(std::string file);
	int getInt(std::stringstream& stream);
	void init(std::string file);

};

#endif