#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	GLuint ID;
	VBO(GLfloat* vertices, GLsizeiptr size);
	VBO(GLfloat* vertices, GLsizeiptr size, GLenum access);
	VBO() {}

	void Bind() const;
	void Unbind() const;
	void Delete();
	GLsizeiptr GetSize() const { return _Size; }

private:
	GLsizeiptr _Size;
};

#endif // !VBO_CLASS_H

