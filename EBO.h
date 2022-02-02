#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	GLuint ID;
	int size;
	EBO(GLuint* indices, GLsizeiptr size);
	EBO() {};

	void Bind() const;
	void Unbind() const;
	void Delete();

	const int GetSize() const { return size; }

};

#endif // !EBO_CLASS_H
