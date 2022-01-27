#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	GLuint ID;
	VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind() const;
	void Unbind() const;
	void Delete();

	GLsizeiptr GetVBOSize() const { return _VBO->GetSize()/_Stride; }

private:
	const VBO* _VBO;
	GLsizeiptr _Stride;
};

#endif // !VAO_CLASS_H

