#ifndef MAP_RENDERER_H
#define MAP_RENDERER_H

#include "Tile.h"
#include "TileRenderer.h"
#include "VAO.h"
#include "VBO.h"
#include "SpriteSheet.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MapRenderer
{
public:

	MapRenderer() {}
	MapRenderer(const SpriteSheet& spriteSheet, const Shader& shader);
	MapRenderer(const SpriteSheet& spriteSheet, const Shader& shader, GLfloat TileWidth, GLfloat TileHeight);

	void init(std::string file);
	void init(std::stringstream mapStream);
	void init(unsigned int width, unsigned int height, unsigned int defTexID);

	bool getTile(int& xLoc, int& yLoc, float mouseX, float mouseY);
	void setTileTex(unsigned int texID, int xLoc, int yLoc);

	void drawMap(glm::mat4 projection) const;

	const VAO& getVAO();

	const static int NUM_QUAD_COMPONENTS = 24;

private:
	int width, height;
	std::vector<GLfloat> vertexArray;
	VAO _VAO;
	VBO _VBO;
	const SpriteSheet* _sSheet;
	const Shader* _Shader;

	GLfloat TileWidth = 1.0f;
	GLfloat TileHeight = 1.0f;

	std::stringstream readMapFile(std::string file);
	int getInt(std::stringstream& stream);
	void genQuad(unsigned int& tLoc, unsigned int tID, int x, int y);

	void loadVBO(std::stringstream& mapStream);
};

#endif