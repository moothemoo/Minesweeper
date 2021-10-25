#include "Map.h"


#include <iostream>
#include <sstream>
#include <fstream>


Map::Map(std::string file, const SpriteSheet& spriteSheet, const Shader& shader)
	:_sSheet(&spriteSheet),
	_Shader(&shader)
{
	init(file);
}

Map::Map(std::string file, const SpriteSheet& spriteSheet, const Shader& shader, GLfloat TileWidth, GLfloat TileHeight)
	:_sSheet(&spriteSheet),
	_Shader(&shader),
	TileWidth(TileWidth),
	TileHeight(TileHeight)
{
	init(file);
}


const VAO& Map::getVAO()
{
	return _VAO;
}

const Tile& Map::getTile(unsigned int x, unsigned int y) const
{
	return TileArray[x][y];
}


bool Map::getTile(int& xLoc, int& yLoc, float mouseX, float mouseY)
{
	xLoc = (int)std::floor((float) mouseX / TileWidth);
	yLoc = (int)std::floor((float) mouseY / TileHeight);

	return (xLoc >= 0 && xLoc < width&& yLoc >= 0 && yLoc < height);
}

void Map::setTileTex(unsigned int texID, int xLoc, int yLoc)
{
	GLfloat left, right, top, bottom;
	_sSheet->GetTexLoc(left, right, top, bottom, texID);

	//std::cout << left << ", " << right << ", " << top << ", " << bottom << std::endl;

	int quadLoc = (xLoc + yLoc * width) * Map::NUM_QUAD_COMPONENTS;

	_VBO.Bind();

	GLfloat *ptr = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	//	   |Bottom Left   | Bottom right  | Top left	  | Top right	  | Top left	  | Bottom right  |
	//	   |Vertex|Texture| Vertex|Texture| Vertex|Texture| Vertex|Texture| Vertex|Texture| Vertex|Texture|
	//	   | 0	1 |	2	3 | 4	5 | 6	7 | 8	9 | 10	11| 12	13| 14	15| 16	17| 18	19| 20	21| 22	23|
	
	//Bottom Left
	ptr[quadLoc + 2] = left;
	ptr[quadLoc + 3] = bottom;
	//Bottom right
	ptr[quadLoc + 6] = right;
	ptr[quadLoc + 7] = bottom;
	//Top left
	ptr[quadLoc + 10] = left;
	ptr[quadLoc + 11] = top;
	//Top right
	ptr[quadLoc + 14] = right;
	ptr[quadLoc + 15] = top;
	//Top left
	ptr[quadLoc + 18] = left;
	ptr[quadLoc + 19] = top;
	//Bottom right
	ptr[quadLoc + 22] = right;
	ptr[quadLoc + 23] = bottom;

	glUnmapBuffer(GL_ARRAY_BUFFER);


	/*ptr = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, (GLintptr)quadLoc, Map::NUM_QUAD_COMPONENTS, GL_MAP_READ_BIT);
	for (int i = 0; i < Map::NUM_QUAD_COMPONENTS; i++)
	{
		std::cout << ptr[i] << ", ";
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);*/
}

void Map::drawMap() const
{
	_Shader->Use();
	_VAO.Bind();
	_sSheet->getTex().Bind(); //bind texture

	glDrawArrays(GL_TRIANGLES, 0, width * height * 6); //width * height = numQuads
}

std::stringstream Map::readMapFile(std::string file)
{
	std::stringstream stream;
	try
	{
		std::ifstream iFile(file);
		stream << iFile.rdbuf();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::MAP: Failed to find load file" << file << std::endl;
	}
	return stream;
}

int Map::getInt(std::stringstream& stream)
{
	int out = (stream.get() << 24);
	out = out | (stream.get() << 16);
	out = out | (stream.get() << 8);
	out = out | (stream.get());
	return out;
}

void Map::init(std::string file)
{
	std::stringstream mapStream = readMapFile(file);

	mapStream.seekg(0, mapStream.end);
	int length = mapStream.tellg();
	mapStream.seekg(0, mapStream.beg);

	width = getInt(mapStream);
	height = getInt(mapStream);

	if (width * height + 8 > length)
	{
		std::cout << "EOF exception in map file " << file << std::endl;
		assert(false);
	}

	vertexArray = std::vector<GLfloat>(width * height * Map::NUM_QUAD_COMPONENTS, 0.0f);
	TileArray = std::vector<std::vector<Tile>>(width, std::vector<Tile>(height));
	unsigned int tLoc = 0;
	unsigned int tID;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			tID = mapStream.get();
			TileArray[x][y] = Tile(tID);

			GLfloat left, right, top, bottom;
			_sSheet->GetTexLoc(left, right, top, bottom, tID);
			//std::cout << left << ", " << right << ", " << top << ", " << bottom << ", " << x << ", " << y << std::endl;

			//Bottom left
			//Vertex location
			vertexArray[tLoc++] = TileWidth * x;
			vertexArray[tLoc++] = TileHeight * y;
			//Texture location
			vertexArray[tLoc++] = left;
			vertexArray[tLoc++] = bottom;

			//Bottom right
			//Vertex location
			vertexArray[tLoc++] = TileWidth * (x + 1);
			vertexArray[tLoc++] = TileHeight * y;
			//Texture location
			vertexArray[tLoc++] = right;
			vertexArray[tLoc++] = bottom;

			//Top left
			//Vertex location
			vertexArray[tLoc++] = TileWidth * x;
			vertexArray[tLoc++] = TileHeight * (y + 1);
			//Texture location
			vertexArray[tLoc++] = left;
			vertexArray[tLoc++] = top;

			//Top right
			//Vertex location
			vertexArray[tLoc++] = TileWidth * (x + 1);
			vertexArray[tLoc++] = TileHeight * (y + 1);
			//Texture location
			vertexArray[tLoc++] = right;
			vertexArray[tLoc++] = top;

			//Top left
			//Vertex location
			vertexArray[tLoc++] = TileWidth * x;
			vertexArray[tLoc++] = TileHeight * (y + 1);
			//Texture location
			vertexArray[tLoc++] = left;
			vertexArray[tLoc++] = top;

			//Bottom right
			//Vertex location
			vertexArray[tLoc++] = TileWidth * (x + 1);
			vertexArray[tLoc++] = TileHeight * y;
			//Texture location
			vertexArray[tLoc++] = right;
			vertexArray[tLoc++] = bottom;


			if (tLoc >= vertexArray.size() + 1) {
				std::cout << "tLoc bad: " << tLoc << ";  vertexArray.size() = " << vertexArray.size() << std::endl;
				assert(false);
			}
		}
	}

	if (tLoc != vertexArray.size()) {
		std::cout << "tLoc bad: " << tLoc << std::endl;
		assert(false);
	}

	/*for (int i = 0; i < (width*height * NUM_QUAD_COMPONENTS); i++)
	{
		std::cout << vertexArray[i] << ", ";
		if (i % 4 == 3)
		{
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;*/


	_VBO = VBO(&vertexArray[0], vertexArray.size() * sizeof(GLfloat), GL_DYNAMIC_DRAW);
	//std::cout << sizeof(vertexArray);

	_VAO.Bind();
	_VBO.Bind();

	_VAO.LinkAttrib(_VBO, 0, 4, GL_FLOAT, 4 * sizeof(GLfloat), (void*)0);

	_VAO.Unbind();
	_VBO.Unbind();
}