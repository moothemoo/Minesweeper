#ifndef CAMERA2D_CLASS_H
#define CAMERA2D_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "Shader.h"

class Camera2D
{
public:
	bool regenProj;

	Camera2D(float width, float height, glm::vec2 position);
	Camera2D() {}

	void Matrix(Shader& shader, const char* uniform);
	void SetPosition(glm::vec2 position);
	void Move(glm::vec2 vector);
	void SetDimensions(glm::vec2 dimensions);
	void RegenProj();
	glm::vec2 GetPosition() const;
	glm::mat4 GetProjection() const;
	glm::vec2 GetDimensions() const;

private:
	float width, height;
	glm::vec2 Position;
	glm::mat4 projection;
};

#endif