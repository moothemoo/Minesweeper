#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <vector>
#include <glad/glad.h>

#include "Texture.h"
#include "Shader.h"
#include "SpriteSheet.h"


// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
class ResourceManager
{
public:
    // resource storage
    static std::map<std::string, Shader>        Shaders;
    static std::map<std::string, Texture2D>     Textures;
    static std::map<std::string, SpriteSheet>   SpriteSheets;
    
    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static const Shader &    LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    // retrieves a stored sader
    static const Shader &    GetShader(std::string name);
    
    // loads (and generates) a texture from file
    static const Texture2D & LoadTexture(const char* file, bool alpha, std::string name);
    // retrieves a stored texture
    static const Texture2D & GetTexture(std::string name);

    // loads (and generates) a spritesheet
    static const SpriteSheet& LoadSpriteSheet(const char* texName, unsigned int numTexWidth, unsigned int numTexHeight, std::string name);
    // retrieves a stored spritesheet
    static const SpriteSheet& GetSpriteSheet(std::string name);



    // properly de-allocates all loaded resources
    static void      Clear();
private:
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }
    // loads and generates a shader from file
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    // loads a single texture from file
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
};

#endif