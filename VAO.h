#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	GLuint ID;
	VAO();

	void LinkVBO(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind() const;
	void Unbind() const;
	void Delete();

	GLsizeiptr GetNumVertices() const { return numVertices; }

private:

	GLsizeiptr numVertices;
};

#endif // !VAO_CLASS_H

