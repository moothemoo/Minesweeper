#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<iostream>
//#include<GLFW/glfw3.h>
#include <stb/stb_image.h>
#include "Shader.h"

class Texture2D
{
public:
    // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    unsigned int ID;
    
    // constructor (sets default texture modes)
    Texture2D();
    // generates texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Delete();
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
    void setFilter(GLenum minFilter, GLenum magFilter);
    void setTextureWrap(GLenum xWrap, GLenum yWrap);

    // texture image dimensions
    unsigned int Width, Height; // width and height of loaded image in pixels
    // texture Format
    unsigned int Internal_Format; // format of texture object
    unsigned int Image_Format; // format of loaded image
    // texture configuration
    unsigned int Wrap_S; // wrapping mode on S axis
    unsigned int Wrap_T; // wrapping mode on T axis
    unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels
};


#endif // !TEXTURE_CLASS_H