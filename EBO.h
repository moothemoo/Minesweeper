#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	GLuint ID;
	EBO(GLuint* indices, GLsizeiptr size);
	EBO() {};

	void Bind() const;
	void Unbind() const;
	void Delete();

};

#endif // !EBO_CLASS_H
